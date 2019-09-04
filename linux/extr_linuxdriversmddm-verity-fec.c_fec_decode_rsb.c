#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
struct dm_verity_io {int dummy; } ;
struct dm_verity_fec_io {unsigned int nbufs; int /*<<< orphan*/  output; } ;
struct dm_verity {int data_dev_block_bits; TYPE_1__* data_dev; int /*<<< orphan*/  digest_size; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMERR_LIMIT (char*,int /*<<< orphan*/ ,unsigned long long,int) ; 
 unsigned int DM_VERITY_FEC_BUF_RS_BITS ; 
 int EILSEQ ; 
 int fec_alloc_bufs (struct dm_verity*,struct dm_verity_fec_io*) ; 
 int fec_decode_bufs (struct dm_verity*,struct dm_verity_fec_io*,scalar_t__,int,unsigned int,int) ; 
 int /*<<< orphan*/  fec_init_bufs (struct dm_verity*,struct dm_verity_fec_io*) ; 
 int fec_read_bufs (struct dm_verity*,struct dm_verity_io*,scalar_t__,scalar_t__,unsigned int,int*) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 
 int verity_hash (struct dm_verity*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  verity_io_hash_req (struct dm_verity*,struct dm_verity_io*) ; 
 int /*<<< orphan*/  verity_io_real_digest (struct dm_verity*,struct dm_verity_io*) ; 
 int /*<<< orphan*/  verity_io_want_digest (struct dm_verity*,struct dm_verity_io*) ; 

__attribute__((used)) static int fec_decode_rsb(struct dm_verity *v, struct dm_verity_io *io,
			  struct dm_verity_fec_io *fio, u64 rsb, u64 offset,
			  bool use_erasures)
{
	int r, neras = 0;
	unsigned pos;

	r = fec_alloc_bufs(v, fio);
	if (unlikely(r < 0))
		return r;

	for (pos = 0; pos < 1 << v->data_dev_block_bits; ) {
		fec_init_bufs(v, fio);

		r = fec_read_bufs(v, io, rsb, offset, pos,
				  use_erasures ? &neras : NULL);
		if (unlikely(r < 0))
			return r;

		r = fec_decode_bufs(v, fio, rsb, r, pos, neras);
		if (r < 0)
			return r;

		pos += fio->nbufs << DM_VERITY_FEC_BUF_RS_BITS;
	}

	/* Always re-validate the corrected block against the expected hash */
	r = verity_hash(v, verity_io_hash_req(v, io), fio->output,
			1 << v->data_dev_block_bits,
			verity_io_real_digest(v, io));
	if (unlikely(r < 0))
		return r;

	if (memcmp(verity_io_real_digest(v, io), verity_io_want_digest(v, io),
		   v->digest_size)) {
		DMERR_LIMIT("%s: FEC %llu: failed to correct (%d erasures)",
			    v->data_dev->name, (unsigned long long)rsb, neras);
		return -EILSEQ;
	}

	return 0;
}