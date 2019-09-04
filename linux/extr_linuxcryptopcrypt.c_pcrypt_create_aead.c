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
typedef  int /*<<< orphan*/  u32 ;
struct rtattr {int dummy; } ;
struct pcrypt_instance_ctx {int /*<<< orphan*/  spawn; } ;
struct pcrypt_aead_ctx {int dummy; } ;
struct crypto_template {int dummy; } ;
typedef  char const crypto_attr_type ;
struct TYPE_3__ {int cra_ctxsize; int /*<<< orphan*/  cra_flags; } ;
struct TYPE_4__ {int /*<<< orphan*/  decrypt; int /*<<< orphan*/  encrypt; int /*<<< orphan*/  setauthsize; int /*<<< orphan*/  setkey; int /*<<< orphan*/  exit; int /*<<< orphan*/  init; TYPE_1__ base; int /*<<< orphan*/  maxauthsize; int /*<<< orphan*/  ivsize; } ;
struct aead_instance {int /*<<< orphan*/  free; TYPE_2__ alg; } ;
struct aead_alg {int /*<<< orphan*/  base; } ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPTO_ALG_ASYNC ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (char const*) ; 
 int PTR_ERR (char const*) ; 
 int /*<<< orphan*/  aead_crypto_instance (struct aead_instance*) ; 
 struct pcrypt_instance_ctx* aead_instance_ctx (struct aead_instance*) ; 
 int aead_register_instance (struct crypto_template*,struct aead_instance*) ; 
 int /*<<< orphan*/  crypto_aead_alg_ivsize (struct aead_alg*) ; 
 int /*<<< orphan*/  crypto_aead_alg_maxauthsize (struct aead_alg*) ; 
 char* crypto_attr_alg_name (struct rtattr*) ; 
 int /*<<< orphan*/  crypto_drop_aead (int /*<<< orphan*/ *) ; 
 char* crypto_get_attr_type (struct rtattr**) ; 
 int crypto_grab_aead (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_set_aead_spawn (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct aead_alg* crypto_spawn_aead_alg (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct aead_instance*) ; 
 struct aead_instance* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pcrypt_aead_decrypt ; 
 int /*<<< orphan*/  pcrypt_aead_encrypt ; 
 int /*<<< orphan*/  pcrypt_aead_exit_tfm ; 
 int /*<<< orphan*/  pcrypt_aead_init_tfm ; 
 int /*<<< orphan*/  pcrypt_aead_setauthsize ; 
 int /*<<< orphan*/  pcrypt_aead_setkey ; 
 int /*<<< orphan*/  pcrypt_free ; 
 int pcrypt_init_instance (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int pcrypt_create_aead(struct crypto_template *tmpl, struct rtattr **tb,
			      u32 type, u32 mask)
{
	struct pcrypt_instance_ctx *ctx;
	struct crypto_attr_type *algt;
	struct aead_instance *inst;
	struct aead_alg *alg;
	const char *name;
	int err;

	algt = crypto_get_attr_type(tb);
	if (IS_ERR(algt))
		return PTR_ERR(algt);

	name = crypto_attr_alg_name(tb[1]);
	if (IS_ERR(name))
		return PTR_ERR(name);

	inst = kzalloc(sizeof(*inst) + sizeof(*ctx), GFP_KERNEL);
	if (!inst)
		return -ENOMEM;

	ctx = aead_instance_ctx(inst);
	crypto_set_aead_spawn(&ctx->spawn, aead_crypto_instance(inst));

	err = crypto_grab_aead(&ctx->spawn, name, 0, 0);
	if (err)
		goto out_free_inst;

	alg = crypto_spawn_aead_alg(&ctx->spawn);
	err = pcrypt_init_instance(aead_crypto_instance(inst), &alg->base);
	if (err)
		goto out_drop_aead;

	inst->alg.base.cra_flags = CRYPTO_ALG_ASYNC;

	inst->alg.ivsize = crypto_aead_alg_ivsize(alg);
	inst->alg.maxauthsize = crypto_aead_alg_maxauthsize(alg);

	inst->alg.base.cra_ctxsize = sizeof(struct pcrypt_aead_ctx);

	inst->alg.init = pcrypt_aead_init_tfm;
	inst->alg.exit = pcrypt_aead_exit_tfm;

	inst->alg.setkey = pcrypt_aead_setkey;
	inst->alg.setauthsize = pcrypt_aead_setauthsize;
	inst->alg.encrypt = pcrypt_aead_encrypt;
	inst->alg.decrypt = pcrypt_aead_decrypt;

	inst->free = pcrypt_free;

	err = aead_register_instance(tmpl, inst);
	if (err)
		goto out_drop_aead;

out:
	return err;

out_drop_aead:
	crypto_drop_aead(&ctx->spawn);
out_free_inst:
	kfree(inst);
	goto out;
}