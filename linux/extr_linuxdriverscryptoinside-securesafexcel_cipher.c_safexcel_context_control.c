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
typedef  int /*<<< orphan*/  u32 ;
struct safexcel_crypto_priv {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int control0; int /*<<< orphan*/  control1; } ;
struct safexcel_command_desc {TYPE_1__ control_data; } ;
struct safexcel_cipher_req {scalar_t__ direction; } ;
struct safexcel_cipher_ctx {int hash_alg; scalar_t__ alg; int key_len; int state_sz; scalar_t__ aead; int /*<<< orphan*/  mode; struct safexcel_crypto_priv* priv; } ;
struct crypto_async_request {int dummy; } ;

/* Variables and functions */
#define  AES_KEYSIZE_128 130 
#define  AES_KEYSIZE_192 129 
#define  AES_KEYSIZE_256 128 
 int CONTEXT_CONTROL_CRYPTO_ALG_3DES ; 
 int CONTEXT_CONTROL_CRYPTO_ALG_AES128 ; 
 int CONTEXT_CONTROL_CRYPTO_ALG_AES192 ; 
 int CONTEXT_CONTROL_CRYPTO_ALG_AES256 ; 
 int CONTEXT_CONTROL_CRYPTO_ALG_DES ; 
 int CONTEXT_CONTROL_DIGEST_HMAC ; 
 int CONTEXT_CONTROL_KEY_EN ; 
 int CONTEXT_CONTROL_SIZE (int) ; 
 int CONTEXT_CONTROL_TYPE_CRYPTO_OUT ; 
 int CONTEXT_CONTROL_TYPE_ENCRYPT_HASH_OUT ; 
 int CONTEXT_CONTROL_TYPE_HASH_DECRYPT_IN ; 
 int CONTEXT_CONTROL_TYPE_NULL_IN ; 
 int EINVAL ; 
 scalar_t__ SAFEXCEL_3DES ; 
 scalar_t__ SAFEXCEL_AES ; 
 scalar_t__ SAFEXCEL_DECRYPT ; 
 scalar_t__ SAFEXCEL_DES ; 
 scalar_t__ SAFEXCEL_ENCRYPT ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int safexcel_context_control(struct safexcel_cipher_ctx *ctx,
				    struct crypto_async_request *async,
				    struct safexcel_cipher_req *sreq,
				    struct safexcel_command_desc *cdesc)
{
	struct safexcel_crypto_priv *priv = ctx->priv;
	int ctrl_size;

	if (ctx->aead) {
		if (sreq->direction == SAFEXCEL_ENCRYPT)
			cdesc->control_data.control0 |= CONTEXT_CONTROL_TYPE_ENCRYPT_HASH_OUT;
		else
			cdesc->control_data.control0 |= CONTEXT_CONTROL_TYPE_HASH_DECRYPT_IN;
	} else {
		cdesc->control_data.control0 |= CONTEXT_CONTROL_TYPE_CRYPTO_OUT;

		/* The decryption control type is a combination of the
		 * encryption type and CONTEXT_CONTROL_TYPE_NULL_IN, for all
		 * types.
		 */
		if (sreq->direction == SAFEXCEL_DECRYPT)
			cdesc->control_data.control0 |= CONTEXT_CONTROL_TYPE_NULL_IN;
	}

	cdesc->control_data.control0 |= CONTEXT_CONTROL_KEY_EN;
	cdesc->control_data.control1 |= ctx->mode;

	if (ctx->aead)
		cdesc->control_data.control0 |= CONTEXT_CONTROL_DIGEST_HMAC |
						ctx->hash_alg;

	if (ctx->alg == SAFEXCEL_DES) {
		cdesc->control_data.control0 |= CONTEXT_CONTROL_CRYPTO_ALG_DES;
	} else if (ctx->alg == SAFEXCEL_3DES) {
		cdesc->control_data.control0 |= CONTEXT_CONTROL_CRYPTO_ALG_3DES;
	} else if (ctx->alg == SAFEXCEL_AES) {
		switch (ctx->key_len) {
		case AES_KEYSIZE_128:
			cdesc->control_data.control0 |= CONTEXT_CONTROL_CRYPTO_ALG_AES128;
			break;
		case AES_KEYSIZE_192:
			cdesc->control_data.control0 |= CONTEXT_CONTROL_CRYPTO_ALG_AES192;
			break;
		case AES_KEYSIZE_256:
			cdesc->control_data.control0 |= CONTEXT_CONTROL_CRYPTO_ALG_AES256;
			break;
		default:
			dev_err(priv->dev, "aes keysize not supported: %u\n",
				ctx->key_len);
			return -EINVAL;
		}
	}

	ctrl_size = ctx->key_len / sizeof(u32);
	if (ctx->aead)
		/* Take in account the ipad+opad digests */
		ctrl_size += ctx->state_sz / sizeof(u32) * 2;
	cdesc->control_data.control0 |= CONTEXT_CONTROL_SIZE(ctrl_size);

	return 0;
}