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
typedef  int /*<<< orphan*/  u8 ;
struct crypto_skcipher {int dummy; } ;
struct crypto_authenc_keys {int /*<<< orphan*/  enckeylen; int /*<<< orphan*/  enckey; int /*<<< orphan*/  authkeylen; int /*<<< orphan*/  authkey; } ;
struct crypto_authenc_ctx {struct crypto_skcipher* enc; struct crypto_ahash* auth; } ;
struct crypto_ahash {int dummy; } ;
struct crypto_aead {int dummy; } ;
typedef  int /*<<< orphan*/  keys ;

/* Variables and functions */
 int CRYPTO_TFM_REQ_MASK ; 
 int CRYPTO_TFM_RES_BAD_KEY_LEN ; 
 int CRYPTO_TFM_RES_MASK ; 
 int EINVAL ; 
 struct crypto_authenc_ctx* crypto_aead_ctx (struct crypto_aead*) ; 
 int crypto_aead_get_flags (struct crypto_aead*) ; 
 int /*<<< orphan*/  crypto_aead_set_flags (struct crypto_aead*,int) ; 
 int /*<<< orphan*/  crypto_ahash_clear_flags (struct crypto_ahash*,int) ; 
 int crypto_ahash_get_flags (struct crypto_ahash*) ; 
 int /*<<< orphan*/  crypto_ahash_set_flags (struct crypto_ahash*,int) ; 
 int crypto_ahash_setkey (struct crypto_ahash*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ crypto_authenc_extractkeys (struct crypto_authenc_keys*,int /*<<< orphan*/  const*,unsigned int) ; 
 int /*<<< orphan*/  crypto_skcipher_clear_flags (struct crypto_skcipher*,int) ; 
 int crypto_skcipher_get_flags (struct crypto_skcipher*) ; 
 int /*<<< orphan*/  crypto_skcipher_set_flags (struct crypto_skcipher*,int) ; 
 int crypto_skcipher_setkey (struct crypto_skcipher*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memzero_explicit (struct crypto_authenc_keys*,int) ; 

__attribute__((used)) static int crypto_authenc_setkey(struct crypto_aead *authenc, const u8 *key,
				 unsigned int keylen)
{
	struct crypto_authenc_ctx *ctx = crypto_aead_ctx(authenc);
	struct crypto_ahash *auth = ctx->auth;
	struct crypto_skcipher *enc = ctx->enc;
	struct crypto_authenc_keys keys;
	int err = -EINVAL;

	if (crypto_authenc_extractkeys(&keys, key, keylen) != 0)
		goto badkey;

	crypto_ahash_clear_flags(auth, CRYPTO_TFM_REQ_MASK);
	crypto_ahash_set_flags(auth, crypto_aead_get_flags(authenc) &
				    CRYPTO_TFM_REQ_MASK);
	err = crypto_ahash_setkey(auth, keys.authkey, keys.authkeylen);
	crypto_aead_set_flags(authenc, crypto_ahash_get_flags(auth) &
				       CRYPTO_TFM_RES_MASK);

	if (err)
		goto out;

	crypto_skcipher_clear_flags(enc, CRYPTO_TFM_REQ_MASK);
	crypto_skcipher_set_flags(enc, crypto_aead_get_flags(authenc) &
				       CRYPTO_TFM_REQ_MASK);
	err = crypto_skcipher_setkey(enc, keys.enckey, keys.enckeylen);
	crypto_aead_set_flags(authenc, crypto_skcipher_get_flags(enc) &
				       CRYPTO_TFM_RES_MASK);

out:
	memzero_explicit(&keys, sizeof(keys));
	return err;

badkey:
	crypto_aead_set_flags(authenc, CRYPTO_TFM_RES_BAD_KEY_LEN);
	goto out;
}