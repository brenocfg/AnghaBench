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
struct blkcipher_walk {unsigned int walk_blocksize; unsigned int alignmask; unsigned int ivsize; int /*<<< orphan*/  iv; scalar_t__ buffer; } ;

/* Variables and functions */
 unsigned int ALIGN (unsigned long,unsigned int) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/ * blkcipher_get_spot (int /*<<< orphan*/ *,unsigned int) ; 
 int crypto_tfm_ctx_alignment () ; 
 scalar_t__ kmalloc (unsigned int,int /*<<< orphan*/ ) ; 
 unsigned int max (unsigned int,unsigned int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static inline int blkcipher_copy_iv(struct blkcipher_walk *walk)
{
	unsigned bs = walk->walk_blocksize;
	unsigned aligned_bs = ALIGN(bs, walk->alignmask + 1);
	unsigned int size = aligned_bs * 2 +
			    walk->ivsize + max(aligned_bs, walk->ivsize) -
			    (walk->alignmask + 1);
	u8 *iv;

	size += walk->alignmask & ~(crypto_tfm_ctx_alignment() - 1);
	walk->buffer = kmalloc(size, GFP_ATOMIC);
	if (!walk->buffer)
		return -ENOMEM;

	iv = (u8 *)ALIGN((unsigned long)walk->buffer, walk->alignmask + 1);
	iv = blkcipher_get_spot(iv, bs) + aligned_bs;
	iv = blkcipher_get_spot(iv, bs) + aligned_bs;
	iv = blkcipher_get_spot(iv, walk->ivsize);

	walk->iv = memcpy(iv, walk->iv, walk->ivsize);
	return 0;
}