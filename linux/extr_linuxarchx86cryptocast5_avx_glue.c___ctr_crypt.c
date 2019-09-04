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
typedef  int /*<<< orphan*/  u64 ;
struct TYPE_7__ {scalar_t__ addr; } ;
struct TYPE_8__ {TYPE_3__ virt; } ;
struct TYPE_5__ {scalar_t__ addr; } ;
struct TYPE_6__ {TYPE_1__ virt; } ;
struct skcipher_walk {unsigned int nbytes; scalar_t__ iv; TYPE_4__ dst; TYPE_2__ src; } ;
struct cast5_ctx {int dummy; } ;
typedef  int /*<<< orphan*/  __be64 ;

/* Variables and functions */
 unsigned int CAST5_BLOCK_SIZE ; 
 unsigned int const CAST5_PARALLEL_BLOCKS ; 
 int /*<<< orphan*/  __cast5_encrypt (struct cast5_ctx*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  be64_add_cpu (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  cast5_ctr_16way (struct cast5_ctx*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static unsigned int __ctr_crypt(struct skcipher_walk *walk,
				struct cast5_ctx *ctx)
{
	const unsigned int bsize = CAST5_BLOCK_SIZE;
	unsigned int nbytes = walk->nbytes;
	u64 *src = (u64 *)walk->src.virt.addr;
	u64 *dst = (u64 *)walk->dst.virt.addr;

	/* Process multi-block batch */
	if (nbytes >= bsize * CAST5_PARALLEL_BLOCKS) {
		do {
			cast5_ctr_16way(ctx, (u8 *)dst, (u8 *)src,
					(__be64 *)walk->iv);

			src += CAST5_PARALLEL_BLOCKS;
			dst += CAST5_PARALLEL_BLOCKS;
			nbytes -= bsize * CAST5_PARALLEL_BLOCKS;
		} while (nbytes >= bsize * CAST5_PARALLEL_BLOCKS);

		if (nbytes < bsize)
			goto done;
	}

	/* Handle leftovers */
	do {
		u64 ctrblk;

		if (dst != src)
			*dst = *src;

		ctrblk = *(u64 *)walk->iv;
		be64_add_cpu((__be64 *)walk->iv, 1);

		__cast5_encrypt(ctx, (u8 *)&ctrblk, (u8 *)&ctrblk);
		*dst ^= ctrblk;

		src += 1;
		dst += 1;
		nbytes -= bsize;
	} while (nbytes >= bsize);

done:
	return nbytes;
}