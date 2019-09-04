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
struct mcryptd_hash_request_ctx {int dummy; } ;
struct mcryptd_hash_ctx {struct crypto_ahash* child; } ;
struct crypto_ahash_spawn {int dummy; } ;
struct hashd_instance_ctx {struct crypto_ahash_spawn spawn; } ;
struct crypto_tfm {int dummy; } ;
struct crypto_instance {int dummy; } ;
struct crypto_ahash {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct crypto_ahash*) ; 
 int PTR_ERR (struct crypto_ahash*) ; 
 int /*<<< orphan*/  __crypto_ahash_cast (struct crypto_tfm*) ; 
 scalar_t__ crypto_ahash_reqsize (struct crypto_ahash*) ; 
 int /*<<< orphan*/  crypto_ahash_set_reqsize (int /*<<< orphan*/ ,scalar_t__) ; 
 struct hashd_instance_ctx* crypto_instance_ctx (struct crypto_instance*) ; 
 struct crypto_ahash* crypto_spawn_ahash (struct crypto_ahash_spawn*) ; 
 struct crypto_instance* crypto_tfm_alg_instance (struct crypto_tfm*) ; 
 struct mcryptd_hash_ctx* crypto_tfm_ctx (struct crypto_tfm*) ; 

__attribute__((used)) static int mcryptd_hash_init_tfm(struct crypto_tfm *tfm)
{
	struct crypto_instance *inst = crypto_tfm_alg_instance(tfm);
	struct hashd_instance_ctx *ictx = crypto_instance_ctx(inst);
	struct crypto_ahash_spawn *spawn = &ictx->spawn;
	struct mcryptd_hash_ctx *ctx = crypto_tfm_ctx(tfm);
	struct crypto_ahash *hash;

	hash = crypto_spawn_ahash(spawn);
	if (IS_ERR(hash))
		return PTR_ERR(hash);

	ctx->child = hash;
	crypto_ahash_set_reqsize(__crypto_ahash_cast(tfm),
				 sizeof(struct mcryptd_hash_request_ctx) +
				 crypto_ahash_reqsize(hash));
	return 0;
}