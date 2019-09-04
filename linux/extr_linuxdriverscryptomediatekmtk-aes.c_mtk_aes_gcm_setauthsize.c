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
typedef  int u32 ;
struct mtk_aes_gcm_ctx {int authsize; } ;
struct mtk_aes_base_ctx {int dummy; } ;
struct crypto_aead {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 struct mtk_aes_base_ctx* crypto_aead_ctx (struct crypto_aead*) ; 
 struct mtk_aes_gcm_ctx* mtk_aes_gcm_ctx_cast (struct mtk_aes_base_ctx*) ; 

__attribute__((used)) static int mtk_aes_gcm_setauthsize(struct crypto_aead *aead,
				   u32 authsize)
{
	struct mtk_aes_base_ctx *ctx = crypto_aead_ctx(aead);
	struct mtk_aes_gcm_ctx *gctx = mtk_aes_gcm_ctx_cast(ctx);

	/* Same as crypto_gcm_authsize() from crypto/gcm.c */
	switch (authsize) {
	case 8:
	case 12:
	case 16:
		break;
	default:
		return -EINVAL;
	}

	gctx->authsize = authsize;
	return 0;
}