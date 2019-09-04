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
typedef  int /*<<< orphan*/  u8 ;
struct device {int dummy; } ;
struct crypto_aead {int dummy; } ;
struct TYPE_2__ {unsigned int keylen; } ;
struct caam_ctx {int /*<<< orphan*/  sh_desc_dec; scalar_t__* drv_ctx; int /*<<< orphan*/  sh_desc_enc; int /*<<< orphan*/  dir; TYPE_1__ cdata; int /*<<< orphan*/  key_dma; int /*<<< orphan*/  key; struct device* jrdev; } ;

/* Variables and functions */
 size_t DECRYPT ; 
 int EINVAL ; 
 size_t ENCRYPT ; 
 int caam_drv_ctx_update (scalar_t__,int /*<<< orphan*/ ) ; 
 struct caam_ctx* crypto_aead_ctx (struct crypto_aead*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  dma_sync_single_for_device (struct device*,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,unsigned int) ; 
 int rfc4106_set_sh_desc (struct crypto_aead*) ; 

__attribute__((used)) static int rfc4106_setkey(struct crypto_aead *aead,
			  const u8 *key, unsigned int keylen)
{
	struct caam_ctx *ctx = crypto_aead_ctx(aead);
	struct device *jrdev = ctx->jrdev;
	int ret;

	if (keylen < 4)
		return -EINVAL;

#ifdef DEBUG
	print_hex_dump(KERN_ERR, "key in @" __stringify(__LINE__)": ",
		       DUMP_PREFIX_ADDRESS, 16, 4, key, keylen, 1);
#endif

	memcpy(ctx->key, key, keylen);
	/*
	 * The last four bytes of the key material are used as the salt value
	 * in the nonce. Update the AES key length.
	 */
	ctx->cdata.keylen = keylen - 4;
	dma_sync_single_for_device(jrdev, ctx->key_dma, ctx->cdata.keylen,
				   ctx->dir);

	ret = rfc4106_set_sh_desc(aead);
	if (ret)
		return ret;

	/* Now update the driver contexts with the new shared descriptor */
	if (ctx->drv_ctx[ENCRYPT]) {
		ret = caam_drv_ctx_update(ctx->drv_ctx[ENCRYPT],
					  ctx->sh_desc_enc);
		if (ret) {
			dev_err(jrdev, "driver enc context update failed\n");
			return ret;
		}
	}

	if (ctx->drv_ctx[DECRYPT]) {
		ret = caam_drv_ctx_update(ctx->drv_ctx[DECRYPT],
					  ctx->sh_desc_dec);
		if (ret) {
			dev_err(jrdev, "driver dec context update failed\n");
			return ret;
		}
	}

	return 0;
}