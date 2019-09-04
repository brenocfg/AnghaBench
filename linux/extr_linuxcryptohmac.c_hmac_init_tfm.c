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
struct shash_desc {int dummy; } ;
struct hmac_ctx {struct crypto_shash* hash; } ;
struct crypto_tfm {scalar_t__ __crt_alg; } ;
struct crypto_shash_spawn {int dummy; } ;
struct crypto_shash {scalar_t__ descsize; } ;
struct crypto_instance {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct crypto_shash*) ; 
 int PTR_ERR (struct crypto_shash*) ; 
 struct crypto_shash* __crypto_shash_cast (struct crypto_tfm*) ; 
 struct crypto_shash_spawn* crypto_instance_ctx (struct crypto_instance*) ; 
 scalar_t__ crypto_shash_descsize (struct crypto_shash*) ; 
 struct crypto_shash* crypto_spawn_shash (struct crypto_shash_spawn*) ; 
 struct hmac_ctx* hmac_ctx (struct crypto_shash*) ; 

__attribute__((used)) static int hmac_init_tfm(struct crypto_tfm *tfm)
{
	struct crypto_shash *parent = __crypto_shash_cast(tfm);
	struct crypto_shash *hash;
	struct crypto_instance *inst = (void *)tfm->__crt_alg;
	struct crypto_shash_spawn *spawn = crypto_instance_ctx(inst);
	struct hmac_ctx *ctx = hmac_ctx(parent);

	hash = crypto_spawn_shash(spawn);
	if (IS_ERR(hash))
		return PTR_ERR(hash);

	parent->descsize = sizeof(struct shash_desc) +
			   crypto_shash_descsize(hash);

	ctx->hash = hash;
	return 0;
}