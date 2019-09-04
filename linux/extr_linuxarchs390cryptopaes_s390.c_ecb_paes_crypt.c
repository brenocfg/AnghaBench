#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  protkey; } ;
struct s390_paes_ctx {unsigned long fc; TYPE_1__ pk; } ;
struct TYPE_9__ {int /*<<< orphan*/  addr; } ;
struct TYPE_10__ {TYPE_4__ virt; } ;
struct TYPE_7__ {int /*<<< orphan*/  addr; } ;
struct TYPE_8__ {TYPE_2__ virt; } ;
struct blkcipher_walk {unsigned int nbytes; TYPE_5__ src; TYPE_3__ dst; } ;
struct blkcipher_desc {int /*<<< orphan*/  tfm; } ;

/* Variables and functions */
 unsigned int AES_BLOCK_SIZE ; 
 unsigned int EIO ; 
 scalar_t__ __paes_set_key (struct s390_paes_ctx*) ; 
 int blkcipher_walk_done (struct blkcipher_desc*,struct blkcipher_walk*,unsigned int) ; 
 int blkcipher_walk_virt (struct blkcipher_desc*,struct blkcipher_walk*) ; 
 unsigned int cpacf_km (unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 struct s390_paes_ctx* crypto_blkcipher_ctx (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ecb_paes_crypt(struct blkcipher_desc *desc,
			  unsigned long modifier,
			  struct blkcipher_walk *walk)
{
	struct s390_paes_ctx *ctx = crypto_blkcipher_ctx(desc->tfm);
	unsigned int nbytes, n, k;
	int ret;

	ret = blkcipher_walk_virt(desc, walk);
	while ((nbytes = walk->nbytes) >= AES_BLOCK_SIZE) {
		/* only use complete blocks */
		n = nbytes & ~(AES_BLOCK_SIZE - 1);
		k = cpacf_km(ctx->fc | modifier, ctx->pk.protkey,
			     walk->dst.virt.addr, walk->src.virt.addr, n);
		if (k)
			ret = blkcipher_walk_done(desc, walk, nbytes - k);
		if (k < n) {
			if (__paes_set_key(ctx) != 0)
				return blkcipher_walk_done(desc, walk, -EIO);
		}
	}
	return ret;
}