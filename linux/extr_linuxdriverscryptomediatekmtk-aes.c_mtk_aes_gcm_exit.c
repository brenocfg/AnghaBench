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
struct mtk_aes_gcm_ctx {int /*<<< orphan*/  ctr; } ;
struct crypto_aead {int dummy; } ;

/* Variables and functions */
 struct mtk_aes_gcm_ctx* crypto_aead_ctx (struct crypto_aead*) ; 
 int /*<<< orphan*/  crypto_free_skcipher (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mtk_aes_gcm_exit(struct crypto_aead *aead)
{
	struct mtk_aes_gcm_ctx *ctx = crypto_aead_ctx(aead);

	crypto_free_skcipher(ctx->ctr);
}