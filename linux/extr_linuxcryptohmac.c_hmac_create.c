#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int cra_blocksize; int cra_ctxsize; int /*<<< orphan*/  cra_exit; int /*<<< orphan*/  cra_init; scalar_t__ cra_alignmask; int /*<<< orphan*/  cra_priority; } ;
struct TYPE_4__ {int digestsize; int statesize; int /*<<< orphan*/  setkey; int /*<<< orphan*/  import; int /*<<< orphan*/  export; int /*<<< orphan*/  finup; int /*<<< orphan*/  final; int /*<<< orphan*/  update; int /*<<< orphan*/  init; TYPE_1__ base; } ;
struct crypto_alg {int cra_blocksize; scalar_t__ cra_alignmask; int /*<<< orphan*/  cra_priority; } ;
struct shash_instance {int digestsize; int statesize; TYPE_2__ alg; struct crypto_alg base; } ;
struct shash_alg {int digestsize; int statesize; TYPE_2__ alg; struct crypto_alg base; } ;
struct rtattr {int dummy; } ;
struct hmac_ctx {int dummy; } ;
struct crypto_template {int dummy; } ;

/* Variables and functions */
 int ALIGN (int,scalar_t__) ; 
 int /*<<< orphan*/  CRYPTO_ALG_TYPE_SHASH ; 
 int EINVAL ; 
 scalar_t__ IS_ERR (struct shash_instance*) ; 
 int PTR_ERR (struct shash_instance*) ; 
 int crypto_check_attr_type (struct rtattr**,int /*<<< orphan*/ ) ; 
 int crypto_init_shash_spawn (int /*<<< orphan*/ ,struct shash_instance*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_mod_put (struct crypto_alg*) ; 
 scalar_t__ crypto_shash_alg_has_setkey (struct shash_instance*) ; 
 scalar_t__ crypto_tfm_ctx_alignment () ; 
 int /*<<< orphan*/  hmac_exit_tfm ; 
 int /*<<< orphan*/  hmac_export ; 
 int /*<<< orphan*/  hmac_final ; 
 int /*<<< orphan*/  hmac_finup ; 
 int /*<<< orphan*/  hmac_import ; 
 int /*<<< orphan*/  hmac_init ; 
 int /*<<< orphan*/  hmac_init_tfm ; 
 int /*<<< orphan*/  hmac_setkey ; 
 int /*<<< orphan*/  hmac_update ; 
 struct shash_instance* shash_alloc_instance (char*,struct crypto_alg*) ; 
 struct shash_instance* shash_attr_alg (struct rtattr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  shash_crypto_instance (struct shash_instance*) ; 
 int /*<<< orphan*/  shash_free_instance (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  shash_instance_ctx (struct shash_instance*) ; 
 int shash_register_instance (struct crypto_template*,struct shash_instance*) ; 

__attribute__((used)) static int hmac_create(struct crypto_template *tmpl, struct rtattr **tb)
{
	struct shash_instance *inst;
	struct crypto_alg *alg;
	struct shash_alg *salg;
	int err;
	int ds;
	int ss;

	err = crypto_check_attr_type(tb, CRYPTO_ALG_TYPE_SHASH);
	if (err)
		return err;

	salg = shash_attr_alg(tb[1], 0, 0);
	if (IS_ERR(salg))
		return PTR_ERR(salg);
	alg = &salg->base;

	/* The underlying hash algorithm must be unkeyed */
	err = -EINVAL;
	if (crypto_shash_alg_has_setkey(salg))
		goto out_put_alg;

	ds = salg->digestsize;
	ss = salg->statesize;
	if (ds > alg->cra_blocksize ||
	    ss < alg->cra_blocksize)
		goto out_put_alg;

	inst = shash_alloc_instance("hmac", alg);
	err = PTR_ERR(inst);
	if (IS_ERR(inst))
		goto out_put_alg;

	err = crypto_init_shash_spawn(shash_instance_ctx(inst), salg,
				      shash_crypto_instance(inst));
	if (err)
		goto out_free_inst;

	inst->alg.base.cra_priority = alg->cra_priority;
	inst->alg.base.cra_blocksize = alg->cra_blocksize;
	inst->alg.base.cra_alignmask = alg->cra_alignmask;

	ss = ALIGN(ss, alg->cra_alignmask + 1);
	inst->alg.digestsize = ds;
	inst->alg.statesize = ss;

	inst->alg.base.cra_ctxsize = sizeof(struct hmac_ctx) +
				     ALIGN(ss * 2, crypto_tfm_ctx_alignment());

	inst->alg.base.cra_init = hmac_init_tfm;
	inst->alg.base.cra_exit = hmac_exit_tfm;

	inst->alg.init = hmac_init;
	inst->alg.update = hmac_update;
	inst->alg.final = hmac_final;
	inst->alg.finup = hmac_finup;
	inst->alg.export = hmac_export;
	inst->alg.import = hmac_import;
	inst->alg.setkey = hmac_setkey;

	err = shash_register_instance(tmpl, inst);
	if (err) {
out_free_inst:
		shash_free_instance(shash_crypto_instance(inst));
	}

out_put_alg:
	crypto_mod_put(alg);
	return err;
}