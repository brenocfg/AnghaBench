#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct device {int /*<<< orphan*/  parent; } ;
struct crypto_authenc_keys {scalar_t__ authkeylen; scalar_t__ enckeylen; int /*<<< orphan*/  enckey; int /*<<< orphan*/  authkey; } ;
struct crypto_aead {int dummy; } ;
struct caam_drv_private {int era; } ;
struct TYPE_3__ {scalar_t__ keylen; } ;
struct TYPE_4__ {scalar_t__ keylen; scalar_t__ keylen_pad; int algtype; } ;
struct caam_ctx {scalar_t__ key; TYPE_1__ cdata; int /*<<< orphan*/  dir; TYPE_2__ adata; int /*<<< orphan*/  key_dma; struct device* jrdev; } ;
typedef  int /*<<< orphan*/  keys ;

/* Variables and functions */
 scalar_t__ CAAM_MAX_KEY_SIZE ; 
 int /*<<< orphan*/  CRYPTO_TFM_RES_BAD_KEY_LEN ; 
 int EINVAL ; 
 int OP_ALG_ALGSEL_MASK ; 
 int aead_set_sh_desc (struct crypto_aead*) ; 
 struct caam_ctx* crypto_aead_ctx (struct crypto_aead*) ; 
 int /*<<< orphan*/  crypto_aead_set_flags (struct crypto_aead*,int /*<<< orphan*/ ) ; 
 scalar_t__ crypto_authenc_extractkeys (struct crypto_authenc_keys*,int /*<<< orphan*/  const*,unsigned int) ; 
 struct caam_drv_private* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_sync_single_for_device (struct device*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int gen_split_key (struct device*,scalar_t__,TYPE_2__*,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  memzero_explicit (struct crypto_authenc_keys*,int) ; 
 scalar_t__ split_key_len (int) ; 

__attribute__((used)) static int aead_setkey(struct crypto_aead *aead,
			       const u8 *key, unsigned int keylen)
{
	struct caam_ctx *ctx = crypto_aead_ctx(aead);
	struct device *jrdev = ctx->jrdev;
	struct caam_drv_private *ctrlpriv = dev_get_drvdata(jrdev->parent);
	struct crypto_authenc_keys keys;
	int ret = 0;

	if (crypto_authenc_extractkeys(&keys, key, keylen) != 0)
		goto badkey;

#ifdef DEBUG
	printk(KERN_ERR "keylen %d enckeylen %d authkeylen %d\n",
	       keys.authkeylen + keys.enckeylen, keys.enckeylen,
	       keys.authkeylen);
	print_hex_dump(KERN_ERR, "key in @"__stringify(__LINE__)": ",
		       DUMP_PREFIX_ADDRESS, 16, 4, key, keylen, 1);
#endif

	/*
	 * If DKP is supported, use it in the shared descriptor to generate
	 * the split key.
	 */
	if (ctrlpriv->era >= 6) {
		ctx->adata.keylen = keys.authkeylen;
		ctx->adata.keylen_pad = split_key_len(ctx->adata.algtype &
						      OP_ALG_ALGSEL_MASK);

		if (ctx->adata.keylen_pad + keys.enckeylen > CAAM_MAX_KEY_SIZE)
			goto badkey;

		memcpy(ctx->key, keys.authkey, keys.authkeylen);
		memcpy(ctx->key + ctx->adata.keylen_pad, keys.enckey,
		       keys.enckeylen);
		dma_sync_single_for_device(jrdev, ctx->key_dma,
					   ctx->adata.keylen_pad +
					   keys.enckeylen, ctx->dir);
		goto skip_split_key;
	}

	ret = gen_split_key(ctx->jrdev, ctx->key, &ctx->adata, keys.authkey,
			    keys.authkeylen, CAAM_MAX_KEY_SIZE -
			    keys.enckeylen);
	if (ret) {
		goto badkey;
	}

	/* postpend encryption key to auth split key */
	memcpy(ctx->key + ctx->adata.keylen_pad, keys.enckey, keys.enckeylen);
	dma_sync_single_for_device(jrdev, ctx->key_dma, ctx->adata.keylen_pad +
				   keys.enckeylen, ctx->dir);
#ifdef DEBUG
	print_hex_dump(KERN_ERR, "ctx.key@"__stringify(__LINE__)": ",
		       DUMP_PREFIX_ADDRESS, 16, 4, ctx->key,
		       ctx->adata.keylen_pad + keys.enckeylen, 1);
#endif

skip_split_key:
	ctx->cdata.keylen = keys.enckeylen;
	memzero_explicit(&keys, sizeof(keys));
	return aead_set_sh_desc(aead);
badkey:
	crypto_aead_set_flags(aead, CRYPTO_TFM_RES_BAD_KEY_LEN);
	memzero_explicit(&keys, sizeof(keys));
	return -EINVAL;
}