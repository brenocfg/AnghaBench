#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct crypto_ablkcipher {int dummy; } ;
struct TYPE_3__ {unsigned int key_len; int /*<<< orphan*/  key; int /*<<< orphan*/  key_sg; int /*<<< orphan*/  mode; int /*<<< orphan*/  type; } ;
struct TYPE_4__ {TYPE_1__ aes; } ;
struct ccp_ctx {TYPE_2__ u; } ;
struct ccp_crypto_ablkcipher_alg {int /*<<< orphan*/  mode; } ;

/* Variables and functions */
#define  AES_KEYSIZE_128 130 
#define  AES_KEYSIZE_192 129 
#define  AES_KEYSIZE_256 128 
 int /*<<< orphan*/  CCP_AES_TYPE_128 ; 
 int /*<<< orphan*/  CCP_AES_TYPE_192 ; 
 int /*<<< orphan*/  CCP_AES_TYPE_256 ; 
 int /*<<< orphan*/  CRYPTO_TFM_RES_BAD_KEY_LEN ; 
 int EINVAL ; 
 struct ccp_crypto_ablkcipher_alg* ccp_crypto_ablkcipher_alg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_ablkcipher_set_flags (struct crypto_ablkcipher*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_ablkcipher_tfm (struct crypto_ablkcipher*) ; 
 struct ccp_ctx* crypto_tfm_ctx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,unsigned int) ; 
 int /*<<< orphan*/  sg_init_one (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int ccp_aes_setkey(struct crypto_ablkcipher *tfm, const u8 *key,
			  unsigned int key_len)
{
	struct ccp_ctx *ctx = crypto_tfm_ctx(crypto_ablkcipher_tfm(tfm));
	struct ccp_crypto_ablkcipher_alg *alg =
		ccp_crypto_ablkcipher_alg(crypto_ablkcipher_tfm(tfm));

	switch (key_len) {
	case AES_KEYSIZE_128:
		ctx->u.aes.type = CCP_AES_TYPE_128;
		break;
	case AES_KEYSIZE_192:
		ctx->u.aes.type = CCP_AES_TYPE_192;
		break;
	case AES_KEYSIZE_256:
		ctx->u.aes.type = CCP_AES_TYPE_256;
		break;
	default:
		crypto_ablkcipher_set_flags(tfm, CRYPTO_TFM_RES_BAD_KEY_LEN);
		return -EINVAL;
	}
	ctx->u.aes.mode = alg->mode;
	ctx->u.aes.key_len = key_len;

	memcpy(ctx->u.aes.key, key, key_len);
	sg_init_one(&ctx->u.aes.key_sg, ctx->u.aes.key, key_len);

	return 0;
}