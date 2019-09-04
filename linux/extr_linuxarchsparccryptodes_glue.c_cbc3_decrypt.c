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
typedef  int /*<<< orphan*/  u64 ;
struct scatterlist {int dummy; } ;
struct des3_ede_sparc64_ctx {int /*<<< orphan*/ * decrypt_expkey; } ;
struct TYPE_7__ {scalar_t__ addr; } ;
struct TYPE_8__ {TYPE_3__ virt; } ;
struct TYPE_5__ {scalar_t__ addr; } ;
struct TYPE_6__ {TYPE_1__ virt; } ;
struct blkcipher_walk {unsigned int nbytes; scalar_t__ iv; TYPE_4__ dst; TYPE_2__ src; } ;
struct blkcipher_desc {int /*<<< orphan*/  flags; int /*<<< orphan*/  tfm; } ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPTO_TFM_REQ_MAY_SLEEP ; 
 unsigned int DES_BLOCK_MASK ; 
 int DES_BLOCK_SIZE ; 
 int blkcipher_walk_done (struct blkcipher_desc*,struct blkcipher_walk*,unsigned int) ; 
 int /*<<< orphan*/  blkcipher_walk_init (struct blkcipher_walk*,struct scatterlist*,struct scatterlist*,unsigned int) ; 
 int blkcipher_walk_virt (struct blkcipher_desc*,struct blkcipher_walk*) ; 
 struct des3_ede_sparc64_ctx* crypto_blkcipher_ctx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  des3_ede_sparc64_cbc_decrypt (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,unsigned int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  des3_ede_sparc64_load_keys (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  fprs_write (int /*<<< orphan*/ ) ; 
 scalar_t__ likely (unsigned int) ; 

__attribute__((used)) static int cbc3_decrypt(struct blkcipher_desc *desc,
			struct scatterlist *dst, struct scatterlist *src,
			unsigned int nbytes)
{
	struct des3_ede_sparc64_ctx *ctx = crypto_blkcipher_ctx(desc->tfm);
	struct blkcipher_walk walk;
	const u64 *K;
	int err;

	blkcipher_walk_init(&walk, dst, src, nbytes);
	err = blkcipher_walk_virt(desc, &walk);
	desc->flags &= ~CRYPTO_TFM_REQ_MAY_SLEEP;

	K = &ctx->decrypt_expkey[0];
	des3_ede_sparc64_load_keys(K);
	while ((nbytes = walk.nbytes)) {
		unsigned int block_len = nbytes & DES_BLOCK_MASK;

		if (likely(block_len)) {
			const u64 *src64 = (const u64 *)walk.src.virt.addr;
			des3_ede_sparc64_cbc_decrypt(K, src64,
						     (u64 *) walk.dst.virt.addr,
						     block_len,
						     (u64 *) walk.iv);
		}
		nbytes &= DES_BLOCK_SIZE - 1;
		err = blkcipher_walk_done(desc, &walk, nbytes);
	}
	fprs_write(0);
	return err;
}