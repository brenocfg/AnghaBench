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
struct omap_aes_ctx {scalar_t__ ctr; } ;
struct crypto_aead {int dummy; } ;

/* Variables and functions */
 struct omap_aes_ctx* crypto_aead_ctx (struct crypto_aead*) ; 
 int /*<<< orphan*/  crypto_aead_tfm (struct crypto_aead*) ; 
 int /*<<< orphan*/  crypto_free_skcipher (scalar_t__) ; 
 int /*<<< orphan*/  omap_aes_cra_exit (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void omap_aes_gcm_cra_exit(struct crypto_aead *tfm)
{
	struct omap_aes_ctx *ctx = crypto_aead_ctx(tfm);

	omap_aes_cra_exit(crypto_aead_tfm(tfm));

	if (ctx->ctr)
		crypto_free_skcipher(ctx->ctr);
}