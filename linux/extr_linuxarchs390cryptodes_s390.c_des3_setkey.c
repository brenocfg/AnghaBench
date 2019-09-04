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
struct s390_des_ctx {int /*<<< orphan*/  key; } ;
struct crypto_tfm {int crt_flags; } ;

/* Variables and functions */
 int CRYPTO_TFM_REQ_WEAK_KEY ; 
 int CRYPTO_TFM_RES_WEAK_KEY ; 
 size_t DES_KEY_SIZE ; 
 int EINVAL ; 
 scalar_t__ crypto_memneq (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,size_t) ; 
 struct s390_des_ctx* crypto_tfm_ctx (struct crypto_tfm*) ; 
 scalar_t__ fips_enabled ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,unsigned int) ; 

__attribute__((used)) static int des3_setkey(struct crypto_tfm *tfm, const u8 *key,
		       unsigned int key_len)
{
	struct s390_des_ctx *ctx = crypto_tfm_ctx(tfm);

	if (!(crypto_memneq(key, &key[DES_KEY_SIZE], DES_KEY_SIZE) &&
	    crypto_memneq(&key[DES_KEY_SIZE], &key[DES_KEY_SIZE * 2],
			  DES_KEY_SIZE)) &&
	    (tfm->crt_flags & CRYPTO_TFM_REQ_WEAK_KEY)) {
		tfm->crt_flags |= CRYPTO_TFM_RES_WEAK_KEY;
		return -EINVAL;
	}

	/* in fips mode, ensure k1 != k2 and k2 != k3 and k1 != k3 */
	if (fips_enabled &&
	    !(crypto_memneq(key, &key[DES_KEY_SIZE], DES_KEY_SIZE) &&
	      crypto_memneq(&key[DES_KEY_SIZE], &key[DES_KEY_SIZE * 2],
			    DES_KEY_SIZE) &&
	      crypto_memneq(key, &key[DES_KEY_SIZE * 2], DES_KEY_SIZE))) {
		tfm->crt_flags |= CRYPTO_TFM_RES_WEAK_KEY;
		return -EINVAL;
	}

	memcpy(ctx->key, key, key_len);
	return 0;
}