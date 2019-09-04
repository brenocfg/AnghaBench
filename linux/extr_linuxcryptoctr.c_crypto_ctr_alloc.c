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
typedef  int u32 ;
struct rtattr {int dummy; } ;
struct TYPE_5__ {int ivsize; char* geniv; void* decrypt; void* encrypt; int /*<<< orphan*/  setkey; int /*<<< orphan*/  max_keysize; int /*<<< orphan*/  min_keysize; } ;
struct TYPE_6__ {int cra_blocksize; int cra_ctxsize; TYPE_2__ cra_blkcipher; int /*<<< orphan*/  cra_exit; int /*<<< orphan*/  cra_init; int /*<<< orphan*/ * cra_type; int /*<<< orphan*/  cra_alignmask; int /*<<< orphan*/  cra_priority; int /*<<< orphan*/  cra_flags; } ;
struct TYPE_4__ {int /*<<< orphan*/  cia_max_keysize; int /*<<< orphan*/  cia_min_keysize; } ;
struct crypto_instance {int cra_blocksize; TYPE_3__ alg; TYPE_1__ cra_cipher; int /*<<< orphan*/  cra_alignmask; int /*<<< orphan*/  cra_priority; int /*<<< orphan*/  mask; int /*<<< orphan*/  type; } ;
struct crypto_ctr_ctx {int dummy; } ;
struct crypto_attr_type {int cra_blocksize; TYPE_3__ alg; TYPE_1__ cra_cipher; int /*<<< orphan*/  cra_alignmask; int /*<<< orphan*/  cra_priority; int /*<<< orphan*/  mask; int /*<<< orphan*/  type; } ;
struct crypto_alg {int cra_blocksize; TYPE_3__ alg; TYPE_1__ cra_cipher; int /*<<< orphan*/  cra_alignmask; int /*<<< orphan*/  cra_priority; int /*<<< orphan*/  mask; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPTO_ALG_NEED_FALLBACK ; 
 int /*<<< orphan*/  CRYPTO_ALG_TYPE_BLKCIPHER ; 
 int /*<<< orphan*/  CRYPTO_ALG_TYPE_CIPHER ; 
 int CRYPTO_ALG_TYPE_MASK ; 
 int EINVAL ; 
 struct crypto_instance* ERR_CAST (struct crypto_instance*) ; 
 struct crypto_instance* ERR_PTR (int) ; 
 scalar_t__ IS_ERR (struct crypto_instance*) ; 
 struct crypto_instance* crypto_alloc_instance (char*,struct crypto_instance*) ; 
 struct crypto_instance* crypto_attr_alg (struct rtattr*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  crypto_blkcipher_type ; 
 int crypto_check_attr_type (struct rtattr**,int /*<<< orphan*/ ) ; 
 void* crypto_ctr_crypt ; 
 int /*<<< orphan*/  crypto_ctr_exit_tfm ; 
 int /*<<< orphan*/  crypto_ctr_init_tfm ; 
 int /*<<< orphan*/  crypto_ctr_setkey ; 
 struct crypto_instance* crypto_get_attr_type (struct rtattr**) ; 
 int /*<<< orphan*/  crypto_mod_put (struct crypto_instance*) ; 
 int crypto_requires_off (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct crypto_instance *crypto_ctr_alloc(struct rtattr **tb)
{
	struct crypto_instance *inst;
	struct crypto_attr_type *algt;
	struct crypto_alg *alg;
	u32 mask;
	int err;

	err = crypto_check_attr_type(tb, CRYPTO_ALG_TYPE_BLKCIPHER);
	if (err)
		return ERR_PTR(err);

	algt = crypto_get_attr_type(tb);
	if (IS_ERR(algt))
		return ERR_CAST(algt);

	mask = CRYPTO_ALG_TYPE_MASK |
		crypto_requires_off(algt->type, algt->mask,
				    CRYPTO_ALG_NEED_FALLBACK);

	alg = crypto_attr_alg(tb[1], CRYPTO_ALG_TYPE_CIPHER, mask);
	if (IS_ERR(alg))
		return ERR_CAST(alg);

	/* Block size must be >= 4 bytes. */
	err = -EINVAL;
	if (alg->cra_blocksize < 4)
		goto out_put_alg;

	/* If this is false we'd fail the alignment of crypto_inc. */
	if (alg->cra_blocksize % 4)
		goto out_put_alg;

	inst = crypto_alloc_instance("ctr", alg);
	if (IS_ERR(inst))
		goto out;

	inst->alg.cra_flags = CRYPTO_ALG_TYPE_BLKCIPHER;
	inst->alg.cra_priority = alg->cra_priority;
	inst->alg.cra_blocksize = 1;
	inst->alg.cra_alignmask = alg->cra_alignmask;
	inst->alg.cra_type = &crypto_blkcipher_type;

	inst->alg.cra_blkcipher.ivsize = alg->cra_blocksize;
	inst->alg.cra_blkcipher.min_keysize = alg->cra_cipher.cia_min_keysize;
	inst->alg.cra_blkcipher.max_keysize = alg->cra_cipher.cia_max_keysize;

	inst->alg.cra_ctxsize = sizeof(struct crypto_ctr_ctx);

	inst->alg.cra_init = crypto_ctr_init_tfm;
	inst->alg.cra_exit = crypto_ctr_exit_tfm;

	inst->alg.cra_blkcipher.setkey = crypto_ctr_setkey;
	inst->alg.cra_blkcipher.encrypt = crypto_ctr_crypt;
	inst->alg.cra_blkcipher.decrypt = crypto_ctr_crypt;

	inst->alg.cra_blkcipher.geniv = "chainiv";

out:
	crypto_mod_put(alg);
	return inst;

out_put_alg:
	inst = ERR_PTR(err);
	goto out;
}