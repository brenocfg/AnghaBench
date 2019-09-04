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
struct xcbc_tfm_ctx {int dummy; } ;
struct xcbc_desc_ctx {int dummy; } ;
struct TYPE_3__ {unsigned long cra_alignmask; int cra_blocksize; int /*<<< orphan*/  cra_exit; int /*<<< orphan*/  cra_init; void* cra_ctxsize; int /*<<< orphan*/  cra_priority; } ;
struct TYPE_4__ {int digestsize; int /*<<< orphan*/  setkey; int /*<<< orphan*/  final; int /*<<< orphan*/  update; int /*<<< orphan*/  init; TYPE_1__ base; void* descsize; } ;
struct shash_instance {int cra_blocksize; int cra_alignmask; TYPE_2__ alg; int /*<<< orphan*/  cra_priority; } ;
struct rtattr {int dummy; } ;
struct crypto_template {int dummy; } ;
struct crypto_alg {int cra_blocksize; int cra_alignmask; TYPE_2__ alg; int /*<<< orphan*/  cra_priority; } ;

/* Variables and functions */
 void* ALIGN (int,unsigned long) ; 
 int /*<<< orphan*/  CRYPTO_ALG_TYPE_CIPHER ; 
 int /*<<< orphan*/  CRYPTO_ALG_TYPE_MASK ; 
 int /*<<< orphan*/  CRYPTO_ALG_TYPE_SHASH ; 
 scalar_t__ IS_ERR (struct shash_instance*) ; 
 int PTR_ERR (struct shash_instance*) ; 
 int crypto_check_attr_type (struct rtattr**,int /*<<< orphan*/ ) ; 
 struct shash_instance* crypto_get_attr_alg (struct rtattr**,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int crypto_init_spawn (int /*<<< orphan*/ ,struct shash_instance*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_mod_put (struct shash_instance*) ; 
 int crypto_tfm_ctx_alignment () ; 
 int /*<<< orphan*/  crypto_xcbc_digest_final ; 
 int /*<<< orphan*/  crypto_xcbc_digest_init ; 
 int /*<<< orphan*/  crypto_xcbc_digest_setkey ; 
 int /*<<< orphan*/  crypto_xcbc_digest_update ; 
 struct shash_instance* shash_alloc_instance (char*,struct shash_instance*) ; 
 int /*<<< orphan*/  shash_crypto_instance (struct shash_instance*) ; 
 int /*<<< orphan*/  shash_free_instance (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  shash_instance_ctx (struct shash_instance*) ; 
 int shash_register_instance (struct crypto_template*,struct shash_instance*) ; 
 int /*<<< orphan*/  xcbc_exit_tfm ; 
 int /*<<< orphan*/  xcbc_init_tfm ; 

__attribute__((used)) static int xcbc_create(struct crypto_template *tmpl, struct rtattr **tb)
{
	struct shash_instance *inst;
	struct crypto_alg *alg;
	unsigned long alignmask;
	int err;

	err = crypto_check_attr_type(tb, CRYPTO_ALG_TYPE_SHASH);
	if (err)
		return err;

	alg = crypto_get_attr_alg(tb, CRYPTO_ALG_TYPE_CIPHER,
				  CRYPTO_ALG_TYPE_MASK);
	if (IS_ERR(alg))
		return PTR_ERR(alg);

	switch(alg->cra_blocksize) {
	case 16:
		break;
	default:
		goto out_put_alg;
	}

	inst = shash_alloc_instance("xcbc", alg);
	err = PTR_ERR(inst);
	if (IS_ERR(inst))
		goto out_put_alg;

	err = crypto_init_spawn(shash_instance_ctx(inst), alg,
				shash_crypto_instance(inst),
				CRYPTO_ALG_TYPE_MASK);
	if (err)
		goto out_free_inst;

	alignmask = alg->cra_alignmask | 3;
	inst->alg.base.cra_alignmask = alignmask;
	inst->alg.base.cra_priority = alg->cra_priority;
	inst->alg.base.cra_blocksize = alg->cra_blocksize;

	inst->alg.digestsize = alg->cra_blocksize;
	inst->alg.descsize = ALIGN(sizeof(struct xcbc_desc_ctx),
				   crypto_tfm_ctx_alignment()) +
			     (alignmask &
			      ~(crypto_tfm_ctx_alignment() - 1)) +
			     alg->cra_blocksize * 2;

	inst->alg.base.cra_ctxsize = ALIGN(sizeof(struct xcbc_tfm_ctx),
					   alignmask + 1) +
				     alg->cra_blocksize * 2;
	inst->alg.base.cra_init = xcbc_init_tfm;
	inst->alg.base.cra_exit = xcbc_exit_tfm;

	inst->alg.init = crypto_xcbc_digest_init;
	inst->alg.update = crypto_xcbc_digest_update;
	inst->alg.final = crypto_xcbc_digest_final;
	inst->alg.setkey = crypto_xcbc_digest_setkey;

	err = shash_register_instance(tmpl, inst);
	if (err) {
out_free_inst:
		shash_free_instance(shash_crypto_instance(inst));
	}

out_put_alg:
	crypto_mod_put(alg);
	return err;
}