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
struct safexcel_crypto_priv {int flags; int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int needs_inv; scalar_t__ ctxr_dma; } ;
struct safexcel_cipher_ctx {int hash_alg; int state_sz; int key_len; int /*<<< orphan*/  opad; int /*<<< orphan*/  ipad; int /*<<< orphan*/  key; TYPE_1__ base; struct safexcel_crypto_priv* priv; } ;
struct safexcel_ahash_export_state {int /*<<< orphan*/ *** state; } ;
struct crypto_tfm {int dummy; } ;
struct crypto_authenc_keys {int enckeylen; int /*<<< orphan*/ **** enckey; int /*<<< orphan*/  authkeylen; int /*<<< orphan*/  authkey; } ;
struct crypto_aead {int dummy; } ;
typedef  int /*<<< orphan*/  keys ;

/* Variables and functions */
#define  CONTEXT_CONTROL_CRYPTO_ALG_SHA1 132 
#define  CONTEXT_CONTROL_CRYPTO_ALG_SHA224 131 
#define  CONTEXT_CONTROL_CRYPTO_ALG_SHA256 130 
#define  CONTEXT_CONTROL_CRYPTO_ALG_SHA384 129 
#define  CONTEXT_CONTROL_CRYPTO_ALG_SHA512 128 
 int CRYPTO_TFM_RES_BAD_KEY_LEN ; 
 int CRYPTO_TFM_RES_MASK ; 
 int EINVAL ; 
 int EIP197_TRC_CACHE ; 
 int crypto_aead_get_flags (struct crypto_aead*) ; 
 int /*<<< orphan*/  crypto_aead_set_flags (struct crypto_aead*,int) ; 
 struct crypto_tfm* crypto_aead_tfm (struct crypto_aead*) ; 
 scalar_t__ crypto_authenc_extractkeys (struct crypto_authenc_keys*,int /*<<< orphan*/  const*,unsigned int) ; 
 struct safexcel_cipher_ctx* crypto_tfm_ctx (struct crypto_tfm*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ **,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ***,int) ; 
 int /*<<< orphan*/  memzero_explicit (struct crypto_authenc_keys*,int) ; 
 int /*<<< orphan*/  safexcel_hmac_setkey (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct safexcel_ahash_export_state*,struct safexcel_ahash_export_state*) ; 

__attribute__((used)) static int safexcel_aead_aes_setkey(struct crypto_aead *ctfm, const u8 *key,
				    unsigned int len)
{
	struct crypto_tfm *tfm = crypto_aead_tfm(ctfm);
	struct safexcel_cipher_ctx *ctx = crypto_tfm_ctx(tfm);
	struct safexcel_ahash_export_state istate, ostate;
	struct safexcel_crypto_priv *priv = ctx->priv;
	struct crypto_authenc_keys keys;

	if (crypto_authenc_extractkeys(&keys, key, len) != 0)
		goto badkey;

	if (keys.enckeylen > sizeof(ctx->key))
		goto badkey;

	/* Encryption key */
	if (priv->flags & EIP197_TRC_CACHE && ctx->base.ctxr_dma &&
	    memcmp(ctx->key, keys.enckey, keys.enckeylen))
		ctx->base.needs_inv = true;

	/* Auth key */
	switch (ctx->hash_alg) {
	case CONTEXT_CONTROL_CRYPTO_ALG_SHA1:
		if (safexcel_hmac_setkey("safexcel-sha1", keys.authkey,
					 keys.authkeylen, &istate, &ostate))
			goto badkey;
		break;
	case CONTEXT_CONTROL_CRYPTO_ALG_SHA224:
		if (safexcel_hmac_setkey("safexcel-sha224", keys.authkey,
					 keys.authkeylen, &istate, &ostate))
			goto badkey;
		break;
	case CONTEXT_CONTROL_CRYPTO_ALG_SHA256:
		if (safexcel_hmac_setkey("safexcel-sha256", keys.authkey,
					 keys.authkeylen, &istate, &ostate))
			goto badkey;
		break;
	case CONTEXT_CONTROL_CRYPTO_ALG_SHA384:
		if (safexcel_hmac_setkey("safexcel-sha384", keys.authkey,
					 keys.authkeylen, &istate, &ostate))
			goto badkey;
		break;
	case CONTEXT_CONTROL_CRYPTO_ALG_SHA512:
		if (safexcel_hmac_setkey("safexcel-sha512", keys.authkey,
					 keys.authkeylen, &istate, &ostate))
			goto badkey;
		break;
	default:
		dev_err(priv->dev, "aead: unsupported hash algorithm\n");
		goto badkey;
	}

	crypto_aead_set_flags(ctfm, crypto_aead_get_flags(ctfm) &
				    CRYPTO_TFM_RES_MASK);

	if (priv->flags & EIP197_TRC_CACHE && ctx->base.ctxr_dma &&
	    (memcmp(ctx->ipad, istate.state, ctx->state_sz) ||
	     memcmp(ctx->opad, ostate.state, ctx->state_sz)))
		ctx->base.needs_inv = true;

	/* Now copy the keys into the context */
	memcpy(ctx->key, keys.enckey, keys.enckeylen);
	ctx->key_len = keys.enckeylen;

	memcpy(ctx->ipad, &istate.state, ctx->state_sz);
	memcpy(ctx->opad, &ostate.state, ctx->state_sz);

	memzero_explicit(&keys, sizeof(keys));
	return 0;

badkey:
	crypto_aead_set_flags(ctfm, CRYPTO_TFM_RES_BAD_KEY_LEN);
	memzero_explicit(&keys, sizeof(keys));
	return -EINVAL;
}