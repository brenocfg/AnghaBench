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
struct crypto_shash_spawn {int dummy; } ;
struct hashd_instance_ctx {struct crypto_shash_spawn spawn; } ;
struct crypto_tfm {int dummy; } ;
struct crypto_shash {int dummy; } ;
struct crypto_instance {int dummy; } ;
struct cryptd_hash_request_ctx {int dummy; } ;
struct cryptd_hash_ctx {struct crypto_shash* child; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct crypto_shash*) ; 
 int PTR_ERR (struct crypto_shash*) ; 
 int /*<<< orphan*/  __crypto_ahash_cast (struct crypto_tfm*) ; 
 int /*<<< orphan*/  crypto_ahash_set_reqsize (int /*<<< orphan*/ ,scalar_t__) ; 
 struct hashd_instance_ctx* crypto_instance_ctx (struct crypto_instance*) ; 
 scalar_t__ crypto_shash_descsize (struct crypto_shash*) ; 
 struct crypto_shash* crypto_spawn_shash (struct crypto_shash_spawn*) ; 
 struct crypto_instance* crypto_tfm_alg_instance (struct crypto_tfm*) ; 
 struct cryptd_hash_ctx* crypto_tfm_ctx (struct crypto_tfm*) ; 

__attribute__((used)) static int cryptd_hash_init_tfm(struct crypto_tfm *tfm)
{
	struct crypto_instance *inst = crypto_tfm_alg_instance(tfm);
	struct hashd_instance_ctx *ictx = crypto_instance_ctx(inst);
	struct crypto_shash_spawn *spawn = &ictx->spawn;
	struct cryptd_hash_ctx *ctx = crypto_tfm_ctx(tfm);
	struct crypto_shash *hash;

	hash = crypto_spawn_shash(spawn);
	if (IS_ERR(hash))
		return PTR_ERR(hash);

	ctx->child = hash;
	crypto_ahash_set_reqsize(__crypto_ahash_cast(tfm),
				 sizeof(struct cryptd_hash_request_ctx) +
				 crypto_shash_descsize(hash));
	return 0;
}