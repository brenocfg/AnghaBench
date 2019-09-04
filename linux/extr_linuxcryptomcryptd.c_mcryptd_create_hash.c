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
typedef  int /*<<< orphan*/  u32 ;
struct rtattr {int dummy; } ;
struct mcryptd_queue {int dummy; } ;
struct mcryptd_hash_ctx {int dummy; } ;
struct hashd_instance_ctx {int /*<<< orphan*/  spawn; struct mcryptd_queue* queue; } ;
struct TYPE_4__ {int cra_flags; int cra_ctxsize; int /*<<< orphan*/  cra_exit; int /*<<< orphan*/  cra_init; } ;
struct TYPE_5__ {TYPE_1__ base; int /*<<< orphan*/  statesize; int /*<<< orphan*/  digestsize; } ;
struct TYPE_6__ {int /*<<< orphan*/  digest; int /*<<< orphan*/  setkey; int /*<<< orphan*/  import; int /*<<< orphan*/  export; int /*<<< orphan*/  finup; int /*<<< orphan*/  final; int /*<<< orphan*/  update; int /*<<< orphan*/  init; TYPE_2__ halg; } ;
struct crypto_alg {int cra_flags; int /*<<< orphan*/  cra_name; } ;
struct hash_alg_common {TYPE_3__ alg; int /*<<< orphan*/  statesize; int /*<<< orphan*/  digestsize; struct crypto_alg base; } ;
struct crypto_template {int dummy; } ;
struct ahash_instance {TYPE_3__ alg; int /*<<< orphan*/  statesize; int /*<<< orphan*/  digestsize; struct crypto_alg base; } ;

/* Variables and functions */
 int CRYPTO_ALG_ASYNC ; 
 int CRYPTO_ALG_INTERNAL ; 
 int CRYPTO_ALG_OPTIONAL_KEY ; 
 int EINVAL ; 
 scalar_t__ IS_ERR (struct hash_alg_common*) ; 
 int PTR_ERR (struct hash_alg_common*) ; 
 struct hash_alg_common* ahash_attr_alg (struct rtattr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ahash_crypto_instance (struct hash_alg_common*) ; 
 struct hashd_instance_ctx* ahash_instance_ctx (struct hash_alg_common*) ; 
 int /*<<< orphan*/  ahash_instance_headroom () ; 
 int ahash_register_instance (struct crypto_template*,struct hash_alg_common*) ; 
 int /*<<< orphan*/  crypto_drop_ahash (int /*<<< orphan*/ *) ; 
 scalar_t__ crypto_hash_alg_has_setkey (struct hash_alg_common*) ; 
 int crypto_init_ahash_spawn (int /*<<< orphan*/ *,struct hash_alg_common*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_mod_put (struct crypto_alg*) ; 
 int /*<<< orphan*/  kfree (struct hash_alg_common*) ; 
 struct hash_alg_common* mcryptd_alloc_instance (struct crypto_alg*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mcryptd_check_internal (struct rtattr**,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mcryptd_hash_digest_enqueue ; 
 int /*<<< orphan*/  mcryptd_hash_exit_tfm ; 
 int /*<<< orphan*/  mcryptd_hash_export ; 
 int /*<<< orphan*/  mcryptd_hash_final_enqueue ; 
 int /*<<< orphan*/  mcryptd_hash_finup_enqueue ; 
 int /*<<< orphan*/  mcryptd_hash_import ; 
 int /*<<< orphan*/  mcryptd_hash_init_enqueue ; 
 int /*<<< orphan*/  mcryptd_hash_init_tfm ; 
 int /*<<< orphan*/  mcryptd_hash_setkey ; 
 int /*<<< orphan*/  mcryptd_hash_update_enqueue ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mcryptd_create_hash(struct crypto_template *tmpl, struct rtattr **tb,
			      struct mcryptd_queue *queue)
{
	struct hashd_instance_ctx *ctx;
	struct ahash_instance *inst;
	struct hash_alg_common *halg;
	struct crypto_alg *alg;
	u32 type = 0;
	u32 mask = 0;
	int err;

	if (!mcryptd_check_internal(tb, &type, &mask))
		return -EINVAL;

	halg = ahash_attr_alg(tb[1], type, mask);
	if (IS_ERR(halg))
		return PTR_ERR(halg);

	alg = &halg->base;
	pr_debug("crypto: mcryptd hash alg: %s\n", alg->cra_name);
	inst = mcryptd_alloc_instance(alg, ahash_instance_headroom(),
					sizeof(*ctx));
	err = PTR_ERR(inst);
	if (IS_ERR(inst))
		goto out_put_alg;

	ctx = ahash_instance_ctx(inst);
	ctx->queue = queue;

	err = crypto_init_ahash_spawn(&ctx->spawn, halg,
				      ahash_crypto_instance(inst));
	if (err)
		goto out_free_inst;

	inst->alg.halg.base.cra_flags = CRYPTO_ALG_ASYNC |
		(alg->cra_flags & (CRYPTO_ALG_INTERNAL |
				   CRYPTO_ALG_OPTIONAL_KEY));

	inst->alg.halg.digestsize = halg->digestsize;
	inst->alg.halg.statesize = halg->statesize;
	inst->alg.halg.base.cra_ctxsize = sizeof(struct mcryptd_hash_ctx);

	inst->alg.halg.base.cra_init = mcryptd_hash_init_tfm;
	inst->alg.halg.base.cra_exit = mcryptd_hash_exit_tfm;

	inst->alg.init   = mcryptd_hash_init_enqueue;
	inst->alg.update = mcryptd_hash_update_enqueue;
	inst->alg.final  = mcryptd_hash_final_enqueue;
	inst->alg.finup  = mcryptd_hash_finup_enqueue;
	inst->alg.export = mcryptd_hash_export;
	inst->alg.import = mcryptd_hash_import;
	if (crypto_hash_alg_has_setkey(halg))
		inst->alg.setkey = mcryptd_hash_setkey;
	inst->alg.digest = mcryptd_hash_digest_enqueue;

	err = ahash_register_instance(tmpl, inst);
	if (err) {
		crypto_drop_ahash(&ctx->spawn);
out_free_inst:
		kfree(inst);
	}

out_put_alg:
	crypto_mod_put(alg);
	return err;
}