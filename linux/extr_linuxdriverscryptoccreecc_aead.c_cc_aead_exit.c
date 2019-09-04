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
struct device {int dummy; } ;
struct crypto_aead {int /*<<< orphan*/  base; } ;
struct cc_xcbc_s {int /*<<< orphan*/ * xcbc_keys; scalar_t__ xcbc_keys_dma_addr; } ;
struct cc_hmac_s {int /*<<< orphan*/ * padded_authkey; scalar_t__ padded_authkey_dma_addr; int /*<<< orphan*/ * ipad_opad; scalar_t__ ipad_opad_dma_addr; } ;
struct TYPE_2__ {struct cc_hmac_s hmac; struct cc_xcbc_s xcbc; } ;
struct cc_aead_ctx {scalar_t__ auth_mode; TYPE_1__ auth_state; int /*<<< orphan*/ * enckey; scalar_t__ enckey_dma_addr; int /*<<< orphan*/  drvdata; } ;

/* Variables and functions */
 int AES_MAX_KEY_SIZE ; 
 int CC_AES_128_BIT_KEY_SIZE ; 
 scalar_t__ DRV_HASH_NULL ; 
 scalar_t__ DRV_HASH_XCBC_MAC ; 
 int MAX_HMAC_BLOCK_SIZE ; 
 int MAX_HMAC_DIGEST_SIZE ; 
 struct cc_aead_ctx* crypto_aead_ctx (struct crypto_aead*) ; 
 int /*<<< orphan*/  crypto_tfm_alg_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,struct cc_aead_ctx*,...) ; 
 int /*<<< orphan*/  dma_free_coherent (struct device*,int,int /*<<< orphan*/ *,scalar_t__) ; 
 struct device* drvdata_to_dev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cc_aead_exit(struct crypto_aead *tfm)
{
	struct cc_aead_ctx *ctx = crypto_aead_ctx(tfm);
	struct device *dev = drvdata_to_dev(ctx->drvdata);

	dev_dbg(dev, "Clearing context @%p for %s\n", crypto_aead_ctx(tfm),
		crypto_tfm_alg_name(&tfm->base));

	/* Unmap enckey buffer */
	if (ctx->enckey) {
		dma_free_coherent(dev, AES_MAX_KEY_SIZE, ctx->enckey,
				  ctx->enckey_dma_addr);
		dev_dbg(dev, "Freed enckey DMA buffer enckey_dma_addr=%pad\n",
			&ctx->enckey_dma_addr);
		ctx->enckey_dma_addr = 0;
		ctx->enckey = NULL;
	}

	if (ctx->auth_mode == DRV_HASH_XCBC_MAC) { /* XCBC authetication */
		struct cc_xcbc_s *xcbc = &ctx->auth_state.xcbc;

		if (xcbc->xcbc_keys) {
			dma_free_coherent(dev, CC_AES_128_BIT_KEY_SIZE * 3,
					  xcbc->xcbc_keys,
					  xcbc->xcbc_keys_dma_addr);
		}
		dev_dbg(dev, "Freed xcbc_keys DMA buffer xcbc_keys_dma_addr=%pad\n",
			&xcbc->xcbc_keys_dma_addr);
		xcbc->xcbc_keys_dma_addr = 0;
		xcbc->xcbc_keys = NULL;
	} else if (ctx->auth_mode != DRV_HASH_NULL) { /* HMAC auth. */
		struct cc_hmac_s *hmac = &ctx->auth_state.hmac;

		if (hmac->ipad_opad) {
			dma_free_coherent(dev, 2 * MAX_HMAC_DIGEST_SIZE,
					  hmac->ipad_opad,
					  hmac->ipad_opad_dma_addr);
			dev_dbg(dev, "Freed ipad_opad DMA buffer ipad_opad_dma_addr=%pad\n",
				&hmac->ipad_opad_dma_addr);
			hmac->ipad_opad_dma_addr = 0;
			hmac->ipad_opad = NULL;
		}
		if (hmac->padded_authkey) {
			dma_free_coherent(dev, MAX_HMAC_BLOCK_SIZE,
					  hmac->padded_authkey,
					  hmac->padded_authkey_dma_addr);
			dev_dbg(dev, "Freed padded_authkey DMA buffer padded_authkey_dma_addr=%pad\n",
				&hmac->padded_authkey_dma_addr);
			hmac->padded_authkey_dma_addr = 0;
			hmac->padded_authkey = NULL;
		}
	}
}