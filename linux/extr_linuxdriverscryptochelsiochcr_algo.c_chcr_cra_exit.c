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
struct crypto_tfm {int dummy; } ;
struct chcr_context {int dummy; } ;
struct ablk_ctx {scalar_t__ aes_generic; int /*<<< orphan*/  sw_cipher; } ;

/* Variables and functions */
 struct ablk_ctx* ABLK_CTX (struct chcr_context*) ; 
 int /*<<< orphan*/  crypto_free_cipher (scalar_t__) ; 
 int /*<<< orphan*/  crypto_free_skcipher (int /*<<< orphan*/ ) ; 
 struct chcr_context* crypto_tfm_ctx (struct crypto_tfm*) ; 

__attribute__((used)) static void chcr_cra_exit(struct crypto_tfm *tfm)
{
	struct chcr_context *ctx = crypto_tfm_ctx(tfm);
	struct ablk_ctx *ablkctx = ABLK_CTX(ctx);

	crypto_free_skcipher(ablkctx->sw_cipher);
	if (ablkctx->aes_generic)
		crypto_free_cipher(ablkctx->aes_generic);
}