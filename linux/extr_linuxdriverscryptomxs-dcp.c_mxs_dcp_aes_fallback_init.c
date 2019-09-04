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
typedef  int uint32_t ;
struct dcp_async_ctx {struct crypto_skcipher* fallback; } ;
struct dcp_aes_req_ctx {int dummy; } ;
struct TYPE_2__ {int reqsize; } ;
struct crypto_tfm {TYPE_1__ crt_ablkcipher; } ;
struct crypto_skcipher {int dummy; } ;

/* Variables and functions */
 int CRYPTO_ALG_ASYNC ; 
 int CRYPTO_ALG_NEED_FALLBACK ; 
 scalar_t__ IS_ERR (struct crypto_skcipher*) ; 
 int PTR_ERR (struct crypto_skcipher*) ; 
 struct crypto_skcipher* crypto_alloc_skcipher (char const*,int /*<<< orphan*/ ,int const) ; 
 char* crypto_tfm_alg_name (struct crypto_tfm*) ; 
 struct dcp_async_ctx* crypto_tfm_ctx (struct crypto_tfm*) ; 

__attribute__((used)) static int mxs_dcp_aes_fallback_init(struct crypto_tfm *tfm)
{
	const char *name = crypto_tfm_alg_name(tfm);
	const uint32_t flags = CRYPTO_ALG_ASYNC | CRYPTO_ALG_NEED_FALLBACK;
	struct dcp_async_ctx *actx = crypto_tfm_ctx(tfm);
	struct crypto_skcipher *blk;

	blk = crypto_alloc_skcipher(name, 0, flags);
	if (IS_ERR(blk))
		return PTR_ERR(blk);

	actx->fallback = blk;
	tfm->crt_ablkcipher.reqsize = sizeof(struct dcp_aes_req_ctx);
	return 0;
}