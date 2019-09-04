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
typedef  int /*<<< orphan*/  u32 ;
struct iproc_ctx_s {int /*<<< orphan*/  cipher_type; } ;
struct crypto_ablkcipher {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CIPHER_TYPE_DES ; 
 int CRYPTO_TFM_REQ_WEAK_KEY ; 
 int /*<<< orphan*/  CRYPTO_TFM_RES_BAD_KEY_LEN ; 
 int /*<<< orphan*/  CRYPTO_TFM_RES_WEAK_KEY ; 
 int DES_EXPKEY_WORDS ; 
 unsigned int DES_KEY_SIZE ; 
 int EINVAL ; 
 struct iproc_ctx_s* crypto_ablkcipher_ctx (struct crypto_ablkcipher*) ; 
 int crypto_ablkcipher_get_flags (struct crypto_ablkcipher*) ; 
 int /*<<< orphan*/  crypto_ablkcipher_set_flags (struct crypto_ablkcipher*,int /*<<< orphan*/ ) ; 
 scalar_t__ des_ekey (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static int des_setkey(struct crypto_ablkcipher *cipher, const u8 *key,
		      unsigned int keylen)
{
	struct iproc_ctx_s *ctx = crypto_ablkcipher_ctx(cipher);
	u32 tmp[DES_EXPKEY_WORDS];

	if (keylen == DES_KEY_SIZE) {
		if (des_ekey(tmp, key) == 0) {
			if (crypto_ablkcipher_get_flags(cipher) &
			    CRYPTO_TFM_REQ_WEAK_KEY) {
				u32 flags = CRYPTO_TFM_RES_WEAK_KEY;

				crypto_ablkcipher_set_flags(cipher, flags);
				return -EINVAL;
			}
		}

		ctx->cipher_type = CIPHER_TYPE_DES;
	} else {
		crypto_ablkcipher_set_flags(cipher, CRYPTO_TFM_RES_BAD_KEY_LEN);
		return -EINVAL;
	}
	return 0;
}