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
typedef  int /*<<< orphan*/  u64 ;
struct scatterlist {int dummy; } ;
struct crypto_sparc64_aes_ctx {int /*<<< orphan*/ * key; TYPE_1__* ops; } ;
struct TYPE_9__ {scalar_t__ addr; } ;
struct TYPE_10__ {TYPE_4__ virt; } ;
struct TYPE_7__ {scalar_t__ addr; } ;
struct TYPE_8__ {TYPE_2__ virt; } ;
struct blkcipher_walk {unsigned int nbytes; scalar_t__ iv; TYPE_5__ dst; TYPE_3__ src; } ;
struct blkcipher_desc {int /*<<< orphan*/  flags; int /*<<< orphan*/  tfm; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* ctr_crypt ) (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,unsigned int,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* load_encrypt_keys ) (int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 unsigned int AES_BLOCK_MASK ; 
 unsigned int AES_BLOCK_SIZE ; 
 int /*<<< orphan*/  CRYPTO_TFM_REQ_MAY_SLEEP ; 
 int blkcipher_walk_done (struct blkcipher_desc*,struct blkcipher_walk*,unsigned int) ; 
 int /*<<< orphan*/  blkcipher_walk_init (struct blkcipher_walk*,struct scatterlist*,struct scatterlist*,unsigned int) ; 
 int blkcipher_walk_virt_block (struct blkcipher_desc*,struct blkcipher_walk*,unsigned int) ; 
 struct crypto_sparc64_aes_ctx* crypto_blkcipher_ctx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ctr_crypt_final (struct crypto_sparc64_aes_ctx*,struct blkcipher_walk*) ; 
 int /*<<< orphan*/  fprs_write (int /*<<< orphan*/ ) ; 
 scalar_t__ likely (unsigned int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,unsigned int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ctr_crypt(struct blkcipher_desc *desc,
		     struct scatterlist *dst, struct scatterlist *src,
		     unsigned int nbytes)
{
	struct crypto_sparc64_aes_ctx *ctx = crypto_blkcipher_ctx(desc->tfm);
	struct blkcipher_walk walk;
	int err;

	blkcipher_walk_init(&walk, dst, src, nbytes);
	err = blkcipher_walk_virt_block(desc, &walk, AES_BLOCK_SIZE);
	desc->flags &= ~CRYPTO_TFM_REQ_MAY_SLEEP;

	ctx->ops->load_encrypt_keys(&ctx->key[0]);
	while ((nbytes = walk.nbytes) >= AES_BLOCK_SIZE) {
		unsigned int block_len = nbytes & AES_BLOCK_MASK;

		if (likely(block_len)) {
			ctx->ops->ctr_crypt(&ctx->key[0],
					    (const u64 *)walk.src.virt.addr,
					    (u64 *) walk.dst.virt.addr,
					    block_len, (u64 *) walk.iv);
		}
		nbytes &= AES_BLOCK_SIZE - 1;
		err = blkcipher_walk_done(desc, &walk, nbytes);
	}
	if (walk.nbytes) {
		ctr_crypt_final(ctx, &walk);
		err = blkcipher_walk_done(desc, &walk, 0);
	}
	fprs_write(0);
	return err;
}