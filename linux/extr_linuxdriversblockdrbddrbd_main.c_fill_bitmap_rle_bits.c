#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct p_compressed_bm {int code; } ;
struct drbd_device {int dummy; } ;
struct bm_xfer_ctx {unsigned long bit_offset; unsigned long bm_bits; int word_offset; } ;
struct TYPE_6__ {int b; int bit; } ;
struct bitstream {TYPE_2__ cur; } ;
struct TYPE_8__ {TYPE_1__* connection; } ;
struct TYPE_7__ {int use_rle; } ;
struct TYPE_5__ {int agreed_pro_version; int /*<<< orphan*/  net_conf; } ;

/* Variables and functions */
 int BITS_PER_LONG ; 
 int ENOBUFS ; 
 unsigned long _drbd_bm_find_next (struct drbd_device*,unsigned long) ; 
 unsigned long _drbd_bm_find_next_zero (struct drbd_device*,unsigned long) ; 
 int /*<<< orphan*/  bitstream_init (struct bitstream*,int,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bm_xfer_ctx_bit_to_word_offset (struct bm_xfer_ctx*) ; 
 int /*<<< orphan*/  dcbp_set_pad_bits (struct p_compressed_bm*,int) ; 
 int /*<<< orphan*/  dcbp_set_start (struct p_compressed_bm*,int) ; 
 int /*<<< orphan*/  drbd_err (struct drbd_device*,char*,int,...) ; 
 TYPE_4__* first_peer_device (struct drbd_device*) ; 
 int /*<<< orphan*/  memset (int,int /*<<< orphan*/ ,unsigned int) ; 
 TYPE_3__* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int vli_encode_bits (struct bitstream*,unsigned long) ; 

__attribute__((used)) static int fill_bitmap_rle_bits(struct drbd_device *device,
			 struct p_compressed_bm *p,
			 unsigned int size,
			 struct bm_xfer_ctx *c)
{
	struct bitstream bs;
	unsigned long plain_bits;
	unsigned long tmp;
	unsigned long rl;
	unsigned len;
	unsigned toggle;
	int bits, use_rle;

	/* may we use this feature? */
	rcu_read_lock();
	use_rle = rcu_dereference(first_peer_device(device)->connection->net_conf)->use_rle;
	rcu_read_unlock();
	if (!use_rle || first_peer_device(device)->connection->agreed_pro_version < 90)
		return 0;

	if (c->bit_offset >= c->bm_bits)
		return 0; /* nothing to do. */

	/* use at most thus many bytes */
	bitstream_init(&bs, p->code, size, 0);
	memset(p->code, 0, size);
	/* plain bits covered in this code string */
	plain_bits = 0;

	/* p->encoding & 0x80 stores whether the first run length is set.
	 * bit offset is implicit.
	 * start with toggle == 2 to be able to tell the first iteration */
	toggle = 2;

	/* see how much plain bits we can stuff into one packet
	 * using RLE and VLI. */
	do {
		tmp = (toggle == 0) ? _drbd_bm_find_next_zero(device, c->bit_offset)
				    : _drbd_bm_find_next(device, c->bit_offset);
		if (tmp == -1UL)
			tmp = c->bm_bits;
		rl = tmp - c->bit_offset;

		if (toggle == 2) { /* first iteration */
			if (rl == 0) {
				/* the first checked bit was set,
				 * store start value, */
				dcbp_set_start(p, 1);
				/* but skip encoding of zero run length */
				toggle = !toggle;
				continue;
			}
			dcbp_set_start(p, 0);
		}

		/* paranoia: catch zero runlength.
		 * can only happen if bitmap is modified while we scan it. */
		if (rl == 0) {
			drbd_err(device, "unexpected zero runlength while encoding bitmap "
			    "t:%u bo:%lu\n", toggle, c->bit_offset);
			return -1;
		}

		bits = vli_encode_bits(&bs, rl);
		if (bits == -ENOBUFS) /* buffer full */
			break;
		if (bits <= 0) {
			drbd_err(device, "error while encoding bitmap: %d\n", bits);
			return 0;
		}

		toggle = !toggle;
		plain_bits += rl;
		c->bit_offset = tmp;
	} while (c->bit_offset < c->bm_bits);

	len = bs.cur.b - p->code + !!bs.cur.bit;

	if (plain_bits < (len << 3)) {
		/* incompressible with this method.
		 * we need to rewind both word and bit position. */
		c->bit_offset -= plain_bits;
		bm_xfer_ctx_bit_to_word_offset(c);
		c->bit_offset = c->word_offset * BITS_PER_LONG;
		return 0;
	}

	/* RLE + VLI was able to compress it just fine.
	 * update c->word_offset. */
	bm_xfer_ctx_bit_to_word_offset(c);

	/* store pad_bits */
	dcbp_set_pad_bits(p, (8 - bs.cur.bit) & 0x7);

	return len;
}