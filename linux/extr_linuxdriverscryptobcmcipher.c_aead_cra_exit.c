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
struct iproc_ctx_s {int /*<<< orphan*/ * fallback_cipher; } ;
struct crypto_tfm {int dummy; } ;
struct crypto_aead {int dummy; } ;

/* Variables and functions */
 struct crypto_tfm* crypto_aead_tfm (struct crypto_aead*) ; 
 int /*<<< orphan*/  crypto_free_aead (int /*<<< orphan*/ *) ; 
 struct iproc_ctx_s* crypto_tfm_ctx (struct crypto_tfm*) ; 
 int /*<<< orphan*/  generic_cra_exit (struct crypto_tfm*) ; 

__attribute__((used)) static void aead_cra_exit(struct crypto_aead *aead)
{
	struct crypto_tfm *tfm = crypto_aead_tfm(aead);
	struct iproc_ctx_s *ctx = crypto_tfm_ctx(tfm);

	generic_cra_exit(tfm);

	if (ctx->fallback_cipher) {
		crypto_free_aead(ctx->fallback_cipher);
		ctx->fallback_cipher = NULL;
	}
}