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
struct cvm_enc_ctx {int key_len; int /*<<< orphan*/  key_type; int /*<<< orphan*/  cipher_type; scalar_t__ enc_key; } ;
struct crypto_tfm {int dummy; } ;
struct crypto_ablkcipher {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AES_128_BIT ; 
 int /*<<< orphan*/  AES_256_BIT ; 
 int /*<<< orphan*/  AES_XTS ; 
 int EINVAL ; 
 scalar_t__ KEY2_OFFSET ; 
 struct crypto_tfm* crypto_ablkcipher_tfm (struct crypto_ablkcipher*) ; 
 struct cvm_enc_ctx* crypto_tfm_ctx (struct crypto_tfm*) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,int /*<<< orphan*/  const*,int) ; 
 int xts_check_key (struct crypto_tfm*,int /*<<< orphan*/  const*,int) ; 

__attribute__((used)) static int cvm_xts_setkey(struct crypto_ablkcipher *cipher, const u8 *key,
		   u32 keylen)
{
	struct crypto_tfm *tfm = crypto_ablkcipher_tfm(cipher);
	struct cvm_enc_ctx *ctx = crypto_tfm_ctx(tfm);
	int err;
	const u8 *key1 = key;
	const u8 *key2 = key + (keylen / 2);

	err = xts_check_key(tfm, key, keylen);
	if (err)
		return err;
	ctx->key_len = keylen;
	memcpy(ctx->enc_key, key1, keylen / 2);
	memcpy(ctx->enc_key + KEY2_OFFSET, key2, keylen / 2);
	ctx->cipher_type = AES_XTS;
	switch (ctx->key_len) {
	case 32:
		ctx->key_type = AES_128_BIT;
		break;
	case 64:
		ctx->key_type = AES_256_BIT;
		break;
	default:
		return -EINVAL;
	}

	return 0;
}