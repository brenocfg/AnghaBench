#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int cra_flags; int cra_ctxsize; int /*<<< orphan*/  cra_alignmask; int /*<<< orphan*/  cra_blocksize; int /*<<< orphan*/  cra_priority; } ;
struct TYPE_6__ {int /*<<< orphan*/  decrypt; int /*<<< orphan*/  encrypt; int /*<<< orphan*/  setkey; int /*<<< orphan*/  exit; int /*<<< orphan*/  init; TYPE_2__ base; int /*<<< orphan*/  max_keysize; int /*<<< orphan*/  min_keysize; int /*<<< orphan*/  ivsize; } ;
struct skcipher_instance {int /*<<< orphan*/  free; TYPE_3__ alg; } ;
struct rtattr {int dummy; } ;
struct crypto_template {int dummy; } ;
struct crypto_spawn {int dummy; } ;
struct crypto_pcbc_ctx {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  cia_max_keysize; int /*<<< orphan*/  cia_min_keysize; } ;
struct crypto_attr_type {int type; int mask; int cra_flags; TYPE_1__ cra_cipher; int /*<<< orphan*/  cra_blocksize; int /*<<< orphan*/  cra_alignmask; int /*<<< orphan*/  cra_priority; } ;
struct crypto_alg {int type; int mask; int cra_flags; TYPE_1__ cra_cipher; int /*<<< orphan*/  cra_blocksize; int /*<<< orphan*/  cra_alignmask; int /*<<< orphan*/  cra_priority; } ;

/* Variables and functions */
 int CRYPTO_ALG_INTERNAL ; 
 int CRYPTO_ALG_TYPE_CIPHER ; 
 int CRYPTO_ALG_TYPE_MASK ; 
 int CRYPTO_ALG_TYPE_SKCIPHER ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct crypto_attr_type*) ; 
 int PTR_ERR (struct crypto_attr_type*) ; 
 int /*<<< orphan*/  crypto_drop_spawn (struct crypto_spawn*) ; 
 struct crypto_attr_type* crypto_get_attr_alg (struct rtattr**,int,int) ; 
 struct crypto_attr_type* crypto_get_attr_type (struct rtattr**) ; 
 int crypto_init_spawn (struct crypto_spawn*,struct crypto_attr_type*,int /*<<< orphan*/ ,int) ; 
 int crypto_inst_setname (int /*<<< orphan*/ ,char*,struct crypto_attr_type*) ; 
 int /*<<< orphan*/  crypto_mod_put (struct crypto_attr_type*) ; 
 int /*<<< orphan*/  crypto_pcbc_decrypt ; 
 int /*<<< orphan*/  crypto_pcbc_encrypt ; 
 int /*<<< orphan*/  crypto_pcbc_exit_tfm ; 
 int /*<<< orphan*/  crypto_pcbc_free ; 
 int /*<<< orphan*/  crypto_pcbc_init_tfm ; 
 int /*<<< orphan*/  crypto_pcbc_setkey ; 
 int /*<<< orphan*/  kfree (struct skcipher_instance*) ; 
 struct skcipher_instance* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skcipher_crypto_instance (struct skcipher_instance*) ; 
 struct crypto_spawn* skcipher_instance_ctx (struct skcipher_instance*) ; 
 int skcipher_register_instance (struct crypto_template*,struct skcipher_instance*) ; 

__attribute__((used)) static int crypto_pcbc_create(struct crypto_template *tmpl, struct rtattr **tb)
{
	struct skcipher_instance *inst;
	struct crypto_attr_type *algt;
	struct crypto_spawn *spawn;
	struct crypto_alg *alg;
	int err;

	algt = crypto_get_attr_type(tb);
	if (IS_ERR(algt))
		return PTR_ERR(algt);

	if (((algt->type ^ CRYPTO_ALG_TYPE_SKCIPHER) & algt->mask) &
	    ~CRYPTO_ALG_INTERNAL)
		return -EINVAL;

	inst = kzalloc(sizeof(*inst) + sizeof(*spawn), GFP_KERNEL);
	if (!inst)
		return -ENOMEM;

	alg = crypto_get_attr_alg(tb, CRYPTO_ALG_TYPE_CIPHER |
				      (algt->type & CRYPTO_ALG_INTERNAL),
				  CRYPTO_ALG_TYPE_MASK |
				  (algt->mask & CRYPTO_ALG_INTERNAL));
	err = PTR_ERR(alg);
	if (IS_ERR(alg))
		goto err_free_inst;

	spawn = skcipher_instance_ctx(inst);
	err = crypto_init_spawn(spawn, alg, skcipher_crypto_instance(inst),
				CRYPTO_ALG_TYPE_MASK);
	if (err)
		goto err_put_alg;

	err = crypto_inst_setname(skcipher_crypto_instance(inst), "pcbc", alg);
	if (err)
		goto err_drop_spawn;

	inst->alg.base.cra_flags = alg->cra_flags & CRYPTO_ALG_INTERNAL;
	inst->alg.base.cra_priority = alg->cra_priority;
	inst->alg.base.cra_blocksize = alg->cra_blocksize;
	inst->alg.base.cra_alignmask = alg->cra_alignmask;

	inst->alg.ivsize = alg->cra_blocksize;
	inst->alg.min_keysize = alg->cra_cipher.cia_min_keysize;
	inst->alg.max_keysize = alg->cra_cipher.cia_max_keysize;

	inst->alg.base.cra_ctxsize = sizeof(struct crypto_pcbc_ctx);

	inst->alg.init = crypto_pcbc_init_tfm;
	inst->alg.exit = crypto_pcbc_exit_tfm;

	inst->alg.setkey = crypto_pcbc_setkey;
	inst->alg.encrypt = crypto_pcbc_encrypt;
	inst->alg.decrypt = crypto_pcbc_decrypt;

	inst->free = crypto_pcbc_free;

	err = skcipher_register_instance(tmpl, inst);
	if (err)
		goto err_drop_spawn;
	crypto_mod_put(alg);

out:
	return err;

err_drop_spawn:
	crypto_drop_spawn(spawn);
err_put_alg:
	crypto_mod_put(alg);
err_free_inst:
	kfree(inst);
	goto out;
}