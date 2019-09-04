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
struct crypto_tfm {int dummy; } ;
struct crypto_aead {int dummy; } ;
struct chcr_aead_ctx {int /*<<< orphan*/  salt; struct crypto_aead* sw_cipher; scalar_t__ enckey_len; } ;

/* Variables and functions */
 struct chcr_aead_ctx* AEAD_CTX (int /*<<< orphan*/ ) ; 
 int CRYPTO_TFM_REQ_MASK ; 
 int /*<<< orphan*/  CRYPTO_TFM_RES_BAD_KEY_LEN ; 
 int CRYPTO_TFM_RES_MASK ; 
 int EINVAL ; 
 int /*<<< orphan*/  a_ctx (struct crypto_aead*) ; 
 int chcr_ccm_common_setkey (struct crypto_aead*,int /*<<< orphan*/  const*,unsigned int) ; 
 int /*<<< orphan*/  crypto_aead_clear_flags (struct crypto_aead*,int) ; 
 int crypto_aead_get_flags (struct crypto_aead*) ; 
 int /*<<< orphan*/  crypto_aead_set_flags (struct crypto_aead*,int) ; 
 int crypto_aead_setkey (struct crypto_aead*,int /*<<< orphan*/  const*,unsigned int) ; 
 int /*<<< orphan*/  crypto_tfm_set_flags (struct crypto_tfm*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int) ; 

__attribute__((used)) static int chcr_aead_rfc4309_setkey(struct crypto_aead *aead, const u8 *key,
				    unsigned int keylen)
{
	struct chcr_aead_ctx *aeadctx = AEAD_CTX(a_ctx(aead));
	int error;

	if (keylen < 3) {
		crypto_tfm_set_flags((struct crypto_tfm *)aead,
				     CRYPTO_TFM_RES_BAD_KEY_LEN);
		aeadctx->enckey_len = 0;
		return	-EINVAL;
	}
	crypto_aead_clear_flags(aeadctx->sw_cipher, CRYPTO_TFM_REQ_MASK);
	crypto_aead_set_flags(aeadctx->sw_cipher, crypto_aead_get_flags(aead) &
			      CRYPTO_TFM_REQ_MASK);
	error = crypto_aead_setkey(aeadctx->sw_cipher, key, keylen);
	crypto_aead_clear_flags(aead, CRYPTO_TFM_RES_MASK);
	crypto_aead_set_flags(aead, crypto_aead_get_flags(aeadctx->sw_cipher) &
			      CRYPTO_TFM_RES_MASK);
	if (error)
		return error;
	keylen -= 3;
	memcpy(aeadctx->salt, key + keylen, 3);
	return chcr_ccm_common_setkey(aead, key, keylen);
}