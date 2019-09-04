#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct ablkcipher_walk {unsigned int nbytes; int /*<<< orphan*/  flags; int /*<<< orphan*/  in; } ;
struct ablkcipher_request {int dummy; } ;
struct ablkcipher_buffer {unsigned int len; void* data; } ;

/* Variables and functions */
 int /*<<< orphan*/  ABLKCIPHER_WALK_SLOW ; 
 unsigned int ALIGN (unsigned long,unsigned int) ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 void* ablkcipher_get_spot (void*,unsigned int) ; 
 int /*<<< orphan*/  ablkcipher_queue_write (struct ablkcipher_walk*,struct ablkcipher_buffer*) ; 
 int ablkcipher_walk_done (struct ablkcipher_request*,struct ablkcipher_walk*,int /*<<< orphan*/ ) ; 
 int crypto_tfm_ctx_alignment () ; 
 struct ablkcipher_buffer* kmalloc (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scatterwalk_copychunks (void*,int /*<<< orphan*/ *,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int ablkcipher_next_slow(struct ablkcipher_request *req,
				       struct ablkcipher_walk *walk,
				       unsigned int bsize,
				       unsigned int alignmask,
				       void **src_p, void **dst_p)
{
	unsigned aligned_bsize = ALIGN(bsize, alignmask + 1);
	struct ablkcipher_buffer *p;
	void *src, *dst, *base;
	unsigned int n;

	n = ALIGN(sizeof(struct ablkcipher_buffer), alignmask + 1);
	n += (aligned_bsize * 3 - (alignmask + 1) +
	      (alignmask & ~(crypto_tfm_ctx_alignment() - 1)));

	p = kmalloc(n, GFP_ATOMIC);
	if (!p)
		return ablkcipher_walk_done(req, walk, -ENOMEM);

	base = p + 1;

	dst = (u8 *)ALIGN((unsigned long)base, alignmask + 1);
	src = dst = ablkcipher_get_spot(dst, bsize);

	p->len = bsize;
	p->data = dst;

	scatterwalk_copychunks(src, &walk->in, bsize, 0);

	ablkcipher_queue_write(walk, p);

	walk->nbytes = bsize;
	walk->flags |= ABLKCIPHER_WALK_SLOW;

	*src_p = src;
	*dst_p = dst;

	return 0;
}