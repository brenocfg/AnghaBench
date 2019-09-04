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
typedef  unsigned int u64 ;
struct scatterlist {int dummy; } ;
struct p8_aes_ctr_ctx {int /*<<< orphan*/  enc_key; int /*<<< orphan*/  fallback; } ;
struct TYPE_7__ {int /*<<< orphan*/  addr; } ;
struct TYPE_8__ {TYPE_3__ virt; } ;
struct TYPE_5__ {int /*<<< orphan*/  addr; } ;
struct TYPE_6__ {TYPE_1__ virt; } ;
struct blkcipher_walk {unsigned int nbytes; int /*<<< orphan*/  iv; TYPE_4__ dst; TYPE_2__ src; } ;
struct blkcipher_desc {int /*<<< orphan*/  info; int /*<<< orphan*/  flags; int /*<<< orphan*/  tfm; } ;

/* Variables and functions */
 unsigned int AES_BLOCK_MASK ; 
 unsigned int AES_BLOCK_SIZE ; 
 int /*<<< orphan*/  SKCIPHER_REQUEST_ON_STACK (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aes_p8_ctr32_encrypt_blocks (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int blkcipher_walk_done (struct blkcipher_desc*,struct blkcipher_walk*,unsigned int) ; 
 int /*<<< orphan*/  blkcipher_walk_init (struct blkcipher_walk*,struct scatterlist*,struct scatterlist*,unsigned int) ; 
 int blkcipher_walk_virt_block (struct blkcipher_desc*,struct blkcipher_walk*,unsigned int) ; 
 int /*<<< orphan*/  crypto_blkcipher_tfm (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_inc (int /*<<< orphan*/ ,unsigned int) ; 
 int crypto_skcipher_encrypt (int /*<<< orphan*/ ) ; 
 struct p8_aes_ctr_ctx* crypto_tfm_ctx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  disable_kernel_vsx () ; 
 int /*<<< orphan*/  enable_kernel_vsx () ; 
 scalar_t__ in_interrupt () ; 
 int /*<<< orphan*/  p8_aes_ctr_final (struct p8_aes_ctr_ctx*,struct blkcipher_walk*) ; 
 int /*<<< orphan*/  pagefault_disable () ; 
 int /*<<< orphan*/  pagefault_enable () ; 
 int /*<<< orphan*/  preempt_disable () ; 
 int /*<<< orphan*/  preempt_enable () ; 
 int /*<<< orphan*/  req ; 
 int /*<<< orphan*/  skcipher_request_set_callback (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skcipher_request_set_crypt (int /*<<< orphan*/ ,struct scatterlist*,struct scatterlist*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skcipher_request_set_tfm (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skcipher_request_zero (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int p8_aes_ctr_crypt(struct blkcipher_desc *desc,
			    struct scatterlist *dst,
			    struct scatterlist *src, unsigned int nbytes)
{
	int ret;
	u64 inc;
	struct blkcipher_walk walk;
	struct p8_aes_ctr_ctx *ctx =
		crypto_tfm_ctx(crypto_blkcipher_tfm(desc->tfm));

	if (in_interrupt()) {
		SKCIPHER_REQUEST_ON_STACK(req, ctx->fallback);
		skcipher_request_set_tfm(req, ctx->fallback);
		skcipher_request_set_callback(req, desc->flags, NULL, NULL);
		skcipher_request_set_crypt(req, src, dst, nbytes, desc->info);
		ret = crypto_skcipher_encrypt(req);
		skcipher_request_zero(req);
	} else {
		blkcipher_walk_init(&walk, dst, src, nbytes);
		ret = blkcipher_walk_virt_block(desc, &walk, AES_BLOCK_SIZE);
		while ((nbytes = walk.nbytes) >= AES_BLOCK_SIZE) {
			preempt_disable();
			pagefault_disable();
			enable_kernel_vsx();
			aes_p8_ctr32_encrypt_blocks(walk.src.virt.addr,
						    walk.dst.virt.addr,
						    (nbytes &
						     AES_BLOCK_MASK) /
						    AES_BLOCK_SIZE,
						    &ctx->enc_key,
						    walk.iv);
			disable_kernel_vsx();
			pagefault_enable();
			preempt_enable();

			/* We need to update IV mostly for last bytes/round */
			inc = (nbytes & AES_BLOCK_MASK) / AES_BLOCK_SIZE;
			if (inc > 0)
				while (inc--)
					crypto_inc(walk.iv, AES_BLOCK_SIZE);

			nbytes &= AES_BLOCK_SIZE - 1;
			ret = blkcipher_walk_done(desc, &walk, nbytes);
		}
		if (walk.nbytes) {
			p8_aes_ctr_final(ctx, &walk);
			ret = blkcipher_walk_done(desc, &walk, 0);
		}
	}

	return ret;
}