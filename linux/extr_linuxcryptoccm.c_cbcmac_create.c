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
struct TYPE_3__ {int cra_blocksize; int cra_ctxsize; int /*<<< orphan*/  cra_exit; int /*<<< orphan*/  cra_init; int /*<<< orphan*/  cra_priority; } ;
struct TYPE_4__ {int /*<<< orphan*/  setkey; int /*<<< orphan*/  final; int /*<<< orphan*/  update; int /*<<< orphan*/  init; TYPE_1__ base; scalar_t__ descsize; scalar_t__ digestsize; } ;
struct shash_instance {TYPE_2__ alg; scalar_t__ cra_blocksize; scalar_t__ cra_alignmask; int /*<<< orphan*/  cra_priority; } ;
struct rtattr {int dummy; } ;
struct crypto_template {int dummy; } ;
struct crypto_alg {TYPE_2__ alg; scalar_t__ cra_blocksize; scalar_t__ cra_alignmask; int /*<<< orphan*/  cra_priority; } ;
struct cbcmac_tfm_ctx {int dummy; } ;
struct cbcmac_desc_ctx {int dummy; } ;

/* Variables and functions */
 scalar_t__ ALIGN (int,scalar_t__) ; 
 int /*<<< orphan*/  CRYPTO_ALG_TYPE_CIPHER ; 
 int /*<<< orphan*/  CRYPTO_ALG_TYPE_MASK ; 
 int /*<<< orphan*/  CRYPTO_ALG_TYPE_SHASH ; 
 scalar_t__ IS_ERR (struct shash_instance*) ; 
 int PTR_ERR (struct shash_instance*) ; 
 int /*<<< orphan*/  cbcmac_exit_tfm ; 
 int /*<<< orphan*/  cbcmac_init_tfm ; 
 int /*<<< orphan*/  crypto_cbcmac_digest_final ; 
 int /*<<< orphan*/  crypto_cbcmac_digest_init ; 
 int /*<<< orphan*/  crypto_cbcmac_digest_setkey ; 
 int /*<<< orphan*/  crypto_cbcmac_digest_update ; 
 int crypto_check_attr_type (struct rtattr**,int /*<<< orphan*/ ) ; 
 struct shash_instance* crypto_get_attr_alg (struct rtattr**,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int crypto_init_spawn (int /*<<< orphan*/ ,struct shash_instance*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_mod_put (struct shash_instance*) ; 
 struct shash_instance* shash_alloc_instance (char*,struct shash_instance*) ; 
 int /*<<< orphan*/  shash_crypto_instance (struct shash_instance*) ; 
 int /*<<< orphan*/  shash_free_instance (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  shash_instance_ctx (struct shash_instance*) ; 
 int shash_register_instance (struct crypto_template*,struct shash_instance*) ; 

__attribute__((used)) static int cbcmac_create(struct crypto_template *tmpl, struct rtattr **tb)
{
	struct shash_instance *inst;
	struct crypto_alg *alg;
	int err;

	err = crypto_check_attr_type(tb, CRYPTO_ALG_TYPE_SHASH);
	if (err)
		return err;

	alg = crypto_get_attr_alg(tb, CRYPTO_ALG_TYPE_CIPHER,
				  CRYPTO_ALG_TYPE_MASK);
	if (IS_ERR(alg))
		return PTR_ERR(alg);

	inst = shash_alloc_instance("cbcmac", alg);
	err = PTR_ERR(inst);
	if (IS_ERR(inst))
		goto out_put_alg;

	err = crypto_init_spawn(shash_instance_ctx(inst), alg,
				shash_crypto_instance(inst),
				CRYPTO_ALG_TYPE_MASK);
	if (err)
		goto out_free_inst;

	inst->alg.base.cra_priority = alg->cra_priority;
	inst->alg.base.cra_blocksize = 1;

	inst->alg.digestsize = alg->cra_blocksize;
	inst->alg.descsize = ALIGN(sizeof(struct cbcmac_desc_ctx),
				   alg->cra_alignmask + 1) +
			     alg->cra_blocksize;

	inst->alg.base.cra_ctxsize = sizeof(struct cbcmac_tfm_ctx);
	inst->alg.base.cra_init = cbcmac_init_tfm;
	inst->alg.base.cra_exit = cbcmac_exit_tfm;

	inst->alg.init = crypto_cbcmac_digest_init;
	inst->alg.update = crypto_cbcmac_digest_update;
	inst->alg.final = crypto_cbcmac_digest_final;
	inst->alg.setkey = crypto_cbcmac_digest_setkey;

	err = shash_register_instance(tmpl, inst);

out_free_inst:
	if (err)
		shash_free_instance(shash_crypto_instance(inst));

out_put_alg:
	crypto_mod_put(alg);
	return err;
}