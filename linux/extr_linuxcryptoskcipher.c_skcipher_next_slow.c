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
typedef  int /*<<< orphan*/  u8 ;
struct skcipher_walk_buffer {unsigned int len; int /*<<< orphan*/ * buffer; } ;
struct TYPE_7__ {int /*<<< orphan*/  addr; } ;
struct TYPE_8__ {TYPE_3__ virt; } ;
struct TYPE_5__ {int /*<<< orphan*/  addr; } ;
struct TYPE_6__ {TYPE_1__ virt; } ;
struct skcipher_walk {int flags; unsigned int alignmask; unsigned int nbytes; int /*<<< orphan*/  in; TYPE_4__ src; TYPE_2__ dst; int /*<<< orphan*/ * buffer; int /*<<< orphan*/ * page; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  PTR_ALIGN (int /*<<< orphan*/ *,unsigned int) ; 
 int SKCIPHER_WALK_PHYS ; 
 int SKCIPHER_WALK_SLOW ; 
 int crypto_tfm_ctx_alignment () ; 
 void* kzalloc (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scatterwalk_copychunks (int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skcipher_get_spot (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  skcipher_queue_write (struct skcipher_walk*,struct skcipher_walk_buffer*) ; 
 int skcipher_walk_done (struct skcipher_walk*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skcipher_walk_gfp (struct skcipher_walk*) ; 

__attribute__((used)) static int skcipher_next_slow(struct skcipher_walk *walk, unsigned int bsize)
{
	bool phys = walk->flags & SKCIPHER_WALK_PHYS;
	unsigned alignmask = walk->alignmask;
	struct skcipher_walk_buffer *p;
	unsigned a;
	unsigned n;
	u8 *buffer;
	void *v;

	if (!phys) {
		if (!walk->buffer)
			walk->buffer = walk->page;
		buffer = walk->buffer;
		if (buffer)
			goto ok;
	}

	/* Start with the minimum alignment of kmalloc. */
	a = crypto_tfm_ctx_alignment() - 1;
	n = bsize;

	if (phys) {
		/* Calculate the minimum alignment of p->buffer. */
		a &= (sizeof(*p) ^ (sizeof(*p) - 1)) >> 1;
		n += sizeof(*p);
	}

	/* Minimum size to align p->buffer by alignmask. */
	n += alignmask & ~a;

	/* Minimum size to ensure p->buffer does not straddle a page. */
	n += (bsize - 1) & ~(alignmask | a);

	v = kzalloc(n, skcipher_walk_gfp(walk));
	if (!v)
		return skcipher_walk_done(walk, -ENOMEM);

	if (phys) {
		p = v;
		p->len = bsize;
		skcipher_queue_write(walk, p);
		buffer = p->buffer;
	} else {
		walk->buffer = v;
		buffer = v;
	}

ok:
	walk->dst.virt.addr = PTR_ALIGN(buffer, alignmask + 1);
	walk->dst.virt.addr = skcipher_get_spot(walk->dst.virt.addr, bsize);
	walk->src.virt.addr = walk->dst.virt.addr;

	scatterwalk_copychunks(walk->src.virt.addr, &walk->in, bsize, 0);

	walk->nbytes = bsize;
	walk->flags |= SKCIPHER_WALK_SLOW;

	return 0;
}