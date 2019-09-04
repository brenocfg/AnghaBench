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
struct shash_desc {int /*<<< orphan*/  tfm; } ;
struct p8_ghash_desc_ctx {int bytes; int /*<<< orphan*/  shash; scalar_t__* buffer; int /*<<< orphan*/  fallback_desc; } ;
struct p8_ghash_ctx {int /*<<< orphan*/  htable; } ;

/* Variables and functions */
 int GHASH_DIGEST_SIZE ; 
 scalar_t__ IN_INTERRUPT ; 
 int crypto_shash_final (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  crypto_shash_tfm (int /*<<< orphan*/ ) ; 
 struct p8_ghash_ctx* crypto_tfm_ctx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  disable_kernel_vsx () ; 
 int /*<<< orphan*/  enable_kernel_vsx () ; 
 int /*<<< orphan*/  gcm_ghash_p8 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pagefault_disable () ; 
 int /*<<< orphan*/  pagefault_enable () ; 
 int /*<<< orphan*/  preempt_disable () ; 
 int /*<<< orphan*/  preempt_enable () ; 
 struct p8_ghash_desc_ctx* shash_desc_ctx (struct shash_desc*) ; 

__attribute__((used)) static int p8_ghash_final(struct shash_desc *desc, u8 *out)
{
	int i;
	struct p8_ghash_ctx *ctx = crypto_tfm_ctx(crypto_shash_tfm(desc->tfm));
	struct p8_ghash_desc_ctx *dctx = shash_desc_ctx(desc);

	if (IN_INTERRUPT) {
		return crypto_shash_final(&dctx->fallback_desc, out);
	} else {
		if (dctx->bytes) {
			for (i = dctx->bytes; i < GHASH_DIGEST_SIZE; i++)
				dctx->buffer[i] = 0;
			preempt_disable();
			pagefault_disable();
			enable_kernel_vsx();
			gcm_ghash_p8(dctx->shash, ctx->htable,
				     dctx->buffer, GHASH_DIGEST_SIZE);
			disable_kernel_vsx();
			pagefault_enable();
			preempt_enable();
			dctx->bytes = 0;
		}
		memcpy(out, dctx->shash, GHASH_DIGEST_SIZE);
		return 0;
	}
}