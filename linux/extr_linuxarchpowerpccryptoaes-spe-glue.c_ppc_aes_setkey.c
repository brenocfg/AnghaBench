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
struct ppc_aes_ctx {int rounds; int /*<<< orphan*/  key_enc; int /*<<< orphan*/  key_dec; } ;
struct crypto_tfm {int /*<<< orphan*/  crt_flags; } ;

/* Variables and functions */
#define  AES_KEYSIZE_128 130 
#define  AES_KEYSIZE_192 129 
#define  AES_KEYSIZE_256 128 
 int /*<<< orphan*/  CRYPTO_TFM_RES_BAD_KEY_LEN ; 
 int EINVAL ; 
 struct ppc_aes_ctx* crypto_tfm_ctx (struct crypto_tfm*) ; 
 int /*<<< orphan*/  ppc_expand_key_128 (int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ppc_expand_key_192 (int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ppc_expand_key_256 (int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ppc_generate_decrypt_key (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int ppc_aes_setkey(struct crypto_tfm *tfm, const u8 *in_key,
		unsigned int key_len)
{
	struct ppc_aes_ctx *ctx = crypto_tfm_ctx(tfm);

	if (key_len != AES_KEYSIZE_128 &&
	    key_len != AES_KEYSIZE_192 &&
	    key_len != AES_KEYSIZE_256) {
		tfm->crt_flags |= CRYPTO_TFM_RES_BAD_KEY_LEN;
		return -EINVAL;
	}

	switch (key_len) {
	case AES_KEYSIZE_128:
		ctx->rounds = 4;
		ppc_expand_key_128(ctx->key_enc, in_key);
		break;
	case AES_KEYSIZE_192:
		ctx->rounds = 5;
		ppc_expand_key_192(ctx->key_enc, in_key);
		break;
	case AES_KEYSIZE_256:
		ctx->rounds = 6;
		ppc_expand_key_256(ctx->key_enc, in_key);
		break;
	}

	ppc_generate_decrypt_key(ctx->key_dec, ctx->key_enc, key_len);

	return 0;
}