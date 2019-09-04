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
struct crypto_tfm {int /*<<< orphan*/  crt_flags; } ;
struct crypto_sparc64_aes_ctx {int expanded_key_length; unsigned int key_length; int /*<<< orphan*/ * key; int /*<<< orphan*/ * ops; } ;

/* Variables and functions */
#define  AES_KEYSIZE_128 130 
#define  AES_KEYSIZE_192 129 
#define  AES_KEYSIZE_256 128 
 int /*<<< orphan*/  CRYPTO_TFM_RES_BAD_KEY_LEN ; 
 int EINVAL ; 
 int /*<<< orphan*/  aes128_ops ; 
 int /*<<< orphan*/  aes192_ops ; 
 int /*<<< orphan*/  aes256_ops ; 
 int /*<<< orphan*/  aes_sparc64_key_expand (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,unsigned int) ; 
 struct crypto_sparc64_aes_ctx* crypto_tfm_ctx (struct crypto_tfm*) ; 

__attribute__((used)) static int aes_set_key(struct crypto_tfm *tfm, const u8 *in_key,
		       unsigned int key_len)
{
	struct crypto_sparc64_aes_ctx *ctx = crypto_tfm_ctx(tfm);
	u32 *flags = &tfm->crt_flags;

	switch (key_len) {
	case AES_KEYSIZE_128:
		ctx->expanded_key_length = 0xb0;
		ctx->ops = &aes128_ops;
		break;

	case AES_KEYSIZE_192:
		ctx->expanded_key_length = 0xd0;
		ctx->ops = &aes192_ops;
		break;

	case AES_KEYSIZE_256:
		ctx->expanded_key_length = 0xf0;
		ctx->ops = &aes256_ops;
		break;

	default:
		*flags |= CRYPTO_TFM_RES_BAD_KEY_LEN;
		return -EINVAL;
	}

	aes_sparc64_key_expand((const u32 *)in_key, &ctx->key[0], key_len);
	ctx->key_length = key_len;

	return 0;
}