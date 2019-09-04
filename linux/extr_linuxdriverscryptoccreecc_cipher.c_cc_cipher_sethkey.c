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
struct crypto_tfm {int dummy; } ;
struct crypto_skcipher {int dummy; } ;
struct cc_hkey_info {unsigned int keylen; unsigned int hw_key1; unsigned int hw_key2; } ;
struct TYPE_2__ {scalar_t__ key1_slot; scalar_t__ key2_slot; } ;
struct cc_cipher_ctx {scalar_t__ flow_mode; scalar_t__ cipher_mode; unsigned int keylen; int hw_key; TYPE_1__ hw; int /*<<< orphan*/  drvdata; } ;
typedef  int /*<<< orphan*/  hki ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPTO_TFM_RES_BAD_KEY_LEN ; 
 scalar_t__ DRV_CIPHER_BITLOCKER ; 
 scalar_t__ DRV_CIPHER_ESSIV ; 
 scalar_t__ DRV_CIPHER_XTS ; 
 int EINVAL ; 
 scalar_t__ END_OF_KEYS ; 
 scalar_t__ S_DIN_to_AES ; 
 void* cc_slot_to_hw_key (unsigned int) ; 
 struct crypto_tfm* crypto_skcipher_tfm (struct crypto_skcipher*) ; 
 int /*<<< orphan*/  crypto_tfm_alg_name (struct crypto_tfm*) ; 
 struct cc_cipher_ctx* crypto_tfm_ctx (struct crypto_tfm*) ; 
 int /*<<< orphan*/  crypto_tfm_set_flags (struct crypto_tfm*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,...) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 struct device* drvdata_to_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dump_byte_array (char*,int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  memcpy (struct cc_hkey_info*,int /*<<< orphan*/  const*,unsigned int) ; 
 scalar_t__ validate_keys_sizes (struct cc_cipher_ctx*,unsigned int) ; 

__attribute__((used)) static int cc_cipher_sethkey(struct crypto_skcipher *sktfm, const u8 *key,
			     unsigned int keylen)
{
	struct crypto_tfm *tfm = crypto_skcipher_tfm(sktfm);
	struct cc_cipher_ctx *ctx_p = crypto_tfm_ctx(tfm);
	struct device *dev = drvdata_to_dev(ctx_p->drvdata);
	struct cc_hkey_info hki;

	dev_dbg(dev, "Setting HW key in context @%p for %s. keylen=%u\n",
		ctx_p, crypto_tfm_alg_name(tfm), keylen);
	dump_byte_array("key", (u8 *)key, keylen);

	/* STAT_PHASE_0: Init and sanity checks */

	/* This check the size of the hardware key token */
	if (keylen != sizeof(hki)) {
		dev_err(dev, "Unsupported HW key size %d.\n", keylen);
		crypto_tfm_set_flags(tfm, CRYPTO_TFM_RES_BAD_KEY_LEN);
		return -EINVAL;
	}

	if (ctx_p->flow_mode != S_DIN_to_AES) {
		dev_err(dev, "HW key not supported for non-AES flows\n");
		return -EINVAL;
	}

	memcpy(&hki, key, keylen);

	/* The real key len for crypto op is the size of the HW key
	 * referenced by the HW key slot, not the hardware key token
	 */
	keylen = hki.keylen;

	if (validate_keys_sizes(ctx_p, keylen)) {
		dev_err(dev, "Unsupported key size %d.\n", keylen);
		crypto_tfm_set_flags(tfm, CRYPTO_TFM_RES_BAD_KEY_LEN);
		return -EINVAL;
	}

	ctx_p->hw.key1_slot = cc_slot_to_hw_key(hki.hw_key1);
	if (ctx_p->hw.key1_slot == END_OF_KEYS) {
		dev_err(dev, "Unsupported hw key1 number (%d)\n", hki.hw_key1);
		return -EINVAL;
	}

	if (ctx_p->cipher_mode == DRV_CIPHER_XTS ||
	    ctx_p->cipher_mode == DRV_CIPHER_ESSIV ||
	    ctx_p->cipher_mode == DRV_CIPHER_BITLOCKER) {
		if (hki.hw_key1 == hki.hw_key2) {
			dev_err(dev, "Illegal hw key numbers (%d,%d)\n",
				hki.hw_key1, hki.hw_key2);
			return -EINVAL;
		}
		ctx_p->hw.key2_slot = cc_slot_to_hw_key(hki.hw_key2);
		if (ctx_p->hw.key2_slot == END_OF_KEYS) {
			dev_err(dev, "Unsupported hw key2 number (%d)\n",
				hki.hw_key2);
			return -EINVAL;
		}
	}

	ctx_p->keylen = keylen;
	ctx_p->hw_key = true;
	dev_dbg(dev, "cc_is_hw_key ret 0");

	return 0;
}