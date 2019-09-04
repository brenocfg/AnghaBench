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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct virtio_crypto_ablkcipher_ctx {int /*<<< orphan*/  tfm; struct virtio_crypto* vcrypto; } ;
struct virtio_crypto {unsigned int max_cipher_key_len; } ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPTO_TFM_RES_BAD_KEY_LEN ; 
 int EINVAL ; 
 int /*<<< orphan*/  crypto_tfm_set_flags (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  virtio_crypto_alg_ablkcipher_close_session (struct virtio_crypto_ablkcipher_ctx*,int) ; 
 int virtio_crypto_alg_ablkcipher_init_session (struct virtio_crypto_ablkcipher_ctx*,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,unsigned int,int) ; 
 scalar_t__ virtio_crypto_alg_validate_key (unsigned int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int virtio_crypto_alg_ablkcipher_init_sessions(
		struct virtio_crypto_ablkcipher_ctx *ctx,
		const uint8_t *key, unsigned int keylen)
{
	uint32_t alg;
	int ret;
	struct virtio_crypto *vcrypto = ctx->vcrypto;

	if (keylen > vcrypto->max_cipher_key_len) {
		pr_err("virtio_crypto: the key is too long\n");
		goto bad_key;
	}

	if (virtio_crypto_alg_validate_key(keylen, &alg))
		goto bad_key;

	/* Create encryption session */
	ret = virtio_crypto_alg_ablkcipher_init_session(ctx,
			alg, key, keylen, 1);
	if (ret)
		return ret;
	/* Create decryption session */
	ret = virtio_crypto_alg_ablkcipher_init_session(ctx,
			alg, key, keylen, 0);
	if (ret) {
		virtio_crypto_alg_ablkcipher_close_session(ctx, 1);
		return ret;
	}
	return 0;

bad_key:
	crypto_tfm_set_flags(ctx->tfm, CRYPTO_TFM_RES_BAD_KEY_LEN);
	return -EINVAL;
}