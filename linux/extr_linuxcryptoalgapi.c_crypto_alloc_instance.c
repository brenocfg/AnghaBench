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
struct crypto_spawn {int dummy; } ;
struct crypto_instance {int dummy; } ;
struct crypto_alg {int dummy; } ;

/* Variables and functions */
 int CRYPTO_ALG_ASYNC ; 
 int CRYPTO_ALG_TYPE_MASK ; 
 struct crypto_instance* ERR_PTR (int) ; 
 scalar_t__ IS_ERR (struct crypto_instance*) ; 
 struct crypto_instance* crypto_alloc_instance2 (char const*,struct crypto_alg*,int /*<<< orphan*/ ) ; 
 int crypto_init_spawn (struct crypto_spawn*,struct crypto_alg*,struct crypto_instance*,int) ; 
 struct crypto_spawn* crypto_instance_ctx (struct crypto_instance*) ; 
 int /*<<< orphan*/  kfree (struct crypto_instance*) ; 

struct crypto_instance *crypto_alloc_instance(const char *name,
					      struct crypto_alg *alg)
{
	struct crypto_instance *inst;
	struct crypto_spawn *spawn;
	int err;

	inst = crypto_alloc_instance2(name, alg, 0);
	if (IS_ERR(inst))
		goto out;

	spawn = crypto_instance_ctx(inst);
	err = crypto_init_spawn(spawn, alg, inst,
				CRYPTO_ALG_TYPE_MASK | CRYPTO_ALG_ASYNC);

	if (err)
		goto err_free_inst;

	return inst;

err_free_inst:
	kfree(inst);
	inst = ERR_PTR(err);

out:
	return inst;
}