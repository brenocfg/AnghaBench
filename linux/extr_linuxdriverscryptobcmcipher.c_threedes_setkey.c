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
struct iproc_ctx_s {int /*<<< orphan*/  cipher_type; } ;
struct crypto_ablkcipher {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CIPHER_TYPE_3DES ; 
 int CRYPTO_TFM_RES_BAD_KEY_LEN ; 
 int CRYPTO_TFM_RES_BAD_KEY_SCHED ; 
 int DES_KEY_SIZE ; 
 int EINVAL ; 
 struct iproc_ctx_s* crypto_ablkcipher_ctx (struct crypto_ablkcipher*) ; 
 int /*<<< orphan*/  crypto_ablkcipher_set_flags (struct crypto_ablkcipher*,int) ; 

__attribute__((used)) static int threedes_setkey(struct crypto_ablkcipher *cipher, const u8 *key,
			   unsigned int keylen)
{
	struct iproc_ctx_s *ctx = crypto_ablkcipher_ctx(cipher);

	if (keylen == (DES_KEY_SIZE * 3)) {
		const u32 *K = (const u32 *)key;
		u32 flags = CRYPTO_TFM_RES_BAD_KEY_SCHED;

		if (!((K[0] ^ K[2]) | (K[1] ^ K[3])) ||
		    !((K[2] ^ K[4]) | (K[3] ^ K[5]))) {
			crypto_ablkcipher_set_flags(cipher, flags);
			return -EINVAL;
		}

		ctx->cipher_type = CIPHER_TYPE_3DES;
	} else {
		crypto_ablkcipher_set_flags(cipher, CRYPTO_TFM_RES_BAD_KEY_LEN);
		return -EINVAL;
	}
	return 0;
}