#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct spacc_req {TYPE_1__* req; } ;
struct spacc_alg {int ctrl_default; } ;
struct spacc_ablk_ctx {scalar_t__ key_len; } ;
struct crypto_tfm {struct crypto_alg* __crt_alg; } ;
struct crypto_alg {int dummy; } ;
struct TYPE_2__ {struct crypto_tfm* tfm; } ;

/* Variables and functions */
 scalar_t__ AES_KEYSIZE_128 ; 
 scalar_t__ AES_KEYSIZE_256 ; 
 int SPACC_CRYPTO_ALG_MASK ; 
 int SPA_CTRL_CIPH_ALG_AES ; 
 struct spacc_ablk_ctx* crypto_tfm_ctx (struct crypto_tfm*) ; 
 struct spacc_alg* to_spacc_alg (struct crypto_alg*) ; 

__attribute__((used)) static int spacc_ablk_need_fallback(struct spacc_req *req)
{
	struct spacc_ablk_ctx *ctx;
	struct crypto_tfm *tfm = req->req->tfm;
	struct crypto_alg *alg = req->req->tfm->__crt_alg;
	struct spacc_alg *spacc_alg = to_spacc_alg(alg);

	ctx = crypto_tfm_ctx(tfm);

	return (spacc_alg->ctrl_default & SPACC_CRYPTO_ALG_MASK) ==
			SPA_CTRL_CIPH_ALG_AES &&
			ctx->key_len != AES_KEYSIZE_128 &&
			ctx->key_len != AES_KEYSIZE_256;
}