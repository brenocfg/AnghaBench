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
typedef  int u32 ;
struct sun4i_tfm_ctx {unsigned int keylen; int /*<<< orphan*/  key; struct sun4i_ss_ctx* ss; } ;
struct sun4i_ss_ctx {int /*<<< orphan*/  dev; } ;
struct crypto_skcipher {int dummy; } ;

/* Variables and functions */
 int CRYPTO_TFM_REQ_WEAK_KEY ; 
 int /*<<< orphan*/  CRYPTO_TFM_RES_BAD_KEY_LEN ; 
 int /*<<< orphan*/  CRYPTO_TFM_RES_WEAK_KEY ; 
 int DES_EXPKEY_WORDS ; 
 unsigned int DES_KEY_SIZE ; 
 int EINVAL ; 
 struct sun4i_tfm_ctx* crypto_skcipher_ctx (struct crypto_skcipher*) ; 
 int crypto_skcipher_get_flags (struct crypto_skcipher*) ; 
 int /*<<< orphan*/  crypto_skcipher_set_flags (struct crypto_skcipher*,int /*<<< orphan*/ ) ; 
 int des_ekey (int*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,unsigned int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,unsigned int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,unsigned int) ; 
 scalar_t__ unlikely (int) ; 

int sun4i_ss_des_setkey(struct crypto_skcipher *tfm, const u8 *key,
			unsigned int keylen)
{
	struct sun4i_tfm_ctx *op = crypto_skcipher_ctx(tfm);
	struct sun4i_ss_ctx *ss = op->ss;
	u32 flags;
	u32 tmp[DES_EXPKEY_WORDS];
	int ret;

	if (unlikely(keylen != DES_KEY_SIZE)) {
		dev_err(ss->dev, "Invalid keylen %u\n", keylen);
		crypto_skcipher_set_flags(tfm, CRYPTO_TFM_RES_BAD_KEY_LEN);
		return -EINVAL;
	}

	flags = crypto_skcipher_get_flags(tfm);

	ret = des_ekey(tmp, key);
	if (unlikely(!ret) && (flags & CRYPTO_TFM_REQ_WEAK_KEY)) {
		crypto_skcipher_set_flags(tfm, CRYPTO_TFM_RES_WEAK_KEY);
		dev_dbg(ss->dev, "Weak key %u\n", keylen);
		return -EINVAL;
	}

	op->keylen = keylen;
	memcpy(op->key, key, keylen);
	return 0;
}