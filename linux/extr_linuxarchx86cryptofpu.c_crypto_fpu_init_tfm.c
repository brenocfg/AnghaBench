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
struct skcipher_instance {int dummy; } ;
struct crypto_skcipher_spawn {int dummy; } ;
struct crypto_skcipher {int dummy; } ;
struct crypto_fpu_ctx {struct crypto_skcipher* child; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct crypto_skcipher*) ; 
 int PTR_ERR (struct crypto_skcipher*) ; 
 struct crypto_fpu_ctx* crypto_skcipher_ctx (struct crypto_skcipher*) ; 
 struct crypto_skcipher* crypto_spawn_skcipher (struct crypto_skcipher_spawn*) ; 
 struct skcipher_instance* skcipher_alg_instance (struct crypto_skcipher*) ; 
 struct crypto_skcipher_spawn* skcipher_instance_ctx (struct skcipher_instance*) ; 

__attribute__((used)) static int crypto_fpu_init_tfm(struct crypto_skcipher *tfm)
{
	struct skcipher_instance *inst = skcipher_alg_instance(tfm);
	struct crypto_fpu_ctx *ctx = crypto_skcipher_ctx(tfm);
	struct crypto_skcipher_spawn *spawn;
	struct crypto_skcipher *cipher;

	spawn = skcipher_instance_ctx(inst);
	cipher = crypto_spawn_skcipher(spawn);
	if (IS_ERR(cipher))
		return PTR_ERR(cipher);

	ctx->child = cipher;

	return 0;
}