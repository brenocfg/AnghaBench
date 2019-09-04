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
struct virtio_crypto_ablkcipher_ctx {struct virtio_crypto* vcrypto; } ;
struct virtio_crypto {int dummy; } ;
struct crypto_ablkcipher {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  VIRTIO_CRYPTO_SERVICE_CIPHER ; 
 struct virtio_crypto_ablkcipher_ctx* crypto_ablkcipher_ctx (struct crypto_ablkcipher*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  virtcrypto_dev_put (struct virtio_crypto*) ; 
 struct virtio_crypto* virtcrypto_get_dev_node (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  virtio_crypto_alg_ablkcipher_close_session (struct virtio_crypto_ablkcipher_ctx*,int) ; 
 int virtio_crypto_alg_ablkcipher_init_sessions (struct virtio_crypto_ablkcipher_ctx*,int /*<<< orphan*/  const*,unsigned int) ; 
 int virtio_crypto_alg_validate_key (unsigned int,int /*<<< orphan*/ *) ; 
 int virtio_crypto_get_current_node () ; 

__attribute__((used)) static int virtio_crypto_ablkcipher_setkey(struct crypto_ablkcipher *tfm,
					 const uint8_t *key,
					 unsigned int keylen)
{
	struct virtio_crypto_ablkcipher_ctx *ctx = crypto_ablkcipher_ctx(tfm);
	uint32_t alg;
	int ret;

	ret = virtio_crypto_alg_validate_key(keylen, &alg);
	if (ret)
		return ret;

	if (!ctx->vcrypto) {
		/* New key */
		int node = virtio_crypto_get_current_node();
		struct virtio_crypto *vcrypto =
				      virtcrypto_get_dev_node(node,
				      VIRTIO_CRYPTO_SERVICE_CIPHER, alg);
		if (!vcrypto) {
			pr_err("virtio_crypto: Could not find a virtio device in the system or unsupported algo\n");
			return -ENODEV;
		}

		ctx->vcrypto = vcrypto;
	} else {
		/* Rekeying, we should close the created sessions previously */
		virtio_crypto_alg_ablkcipher_close_session(ctx, 1);
		virtio_crypto_alg_ablkcipher_close_session(ctx, 0);
	}

	ret = virtio_crypto_alg_ablkcipher_init_sessions(ctx, key, keylen);
	if (ret) {
		virtcrypto_dev_put(ctx->vcrypto);
		ctx->vcrypto = NULL;

		return ret;
	}

	return 0;
}