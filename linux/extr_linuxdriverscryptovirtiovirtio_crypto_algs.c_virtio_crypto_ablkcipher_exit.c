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
struct virtio_crypto_ablkcipher_ctx {int /*<<< orphan*/ * vcrypto; } ;
struct crypto_tfm {int dummy; } ;

/* Variables and functions */
 struct virtio_crypto_ablkcipher_ctx* crypto_tfm_ctx (struct crypto_tfm*) ; 
 int /*<<< orphan*/  virtcrypto_dev_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  virtio_crypto_alg_ablkcipher_close_session (struct virtio_crypto_ablkcipher_ctx*,int) ; 

__attribute__((used)) static void virtio_crypto_ablkcipher_exit(struct crypto_tfm *tfm)
{
	struct virtio_crypto_ablkcipher_ctx *ctx = crypto_tfm_ctx(tfm);

	if (!ctx->vcrypto)
		return;

	virtio_crypto_alg_ablkcipher_close_session(ctx, 1);
	virtio_crypto_alg_ablkcipher_close_session(ctx, 0);
	virtcrypto_dev_put(ctx->vcrypto);
	ctx->vcrypto = NULL;
}