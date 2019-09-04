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
struct list_head {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  ivsize; } ;
struct TYPE_4__ {int /*<<< orphan*/  cra_name; TYPE_1__ cra_ablkcipher; int /*<<< orphan*/  cra_blocksize; int /*<<< orphan*/  cra_driver_name; } ;
struct aead_alg {TYPE_2__ base; } ;
struct ccp_crypto_aead {int /*<<< orphan*/  entry; struct aead_alg alg; int /*<<< orphan*/  mode; } ;
struct ccp_aes_aead_def {char* name; char* driver_name; int /*<<< orphan*/  ivsize; int /*<<< orphan*/  blocksize; struct aead_alg* alg_defaults; int /*<<< orphan*/  mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPTO_MAX_ALG_NAME ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int crypto_register_aead (struct aead_alg*) ; 
 int /*<<< orphan*/  kfree (struct ccp_crypto_aead*) ; 
 struct ccp_crypto_aead* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,struct list_head*) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*) ; 

__attribute__((used)) static int ccp_register_aes_aead(struct list_head *head,
				 const struct ccp_aes_aead_def *def)
{
	struct ccp_crypto_aead *ccp_aead;
	struct aead_alg *alg;
	int ret;

	ccp_aead = kzalloc(sizeof(*ccp_aead), GFP_KERNEL);
	if (!ccp_aead)
		return -ENOMEM;

	INIT_LIST_HEAD(&ccp_aead->entry);

	ccp_aead->mode = def->mode;

	/* Copy the defaults and override as necessary */
	alg = &ccp_aead->alg;
	*alg = *def->alg_defaults;
	snprintf(alg->base.cra_name, CRYPTO_MAX_ALG_NAME, "%s", def->name);
	snprintf(alg->base.cra_driver_name, CRYPTO_MAX_ALG_NAME, "%s",
		 def->driver_name);
	alg->base.cra_blocksize = def->blocksize;
	alg->base.cra_ablkcipher.ivsize = def->ivsize;

	ret = crypto_register_aead(alg);
	if (ret) {
		pr_err("%s ablkcipher algorithm registration error (%d)\n",
		       alg->base.cra_name, ret);
		kfree(ccp_aead);
		return ret;
	}

	list_add(&ccp_aead->entry, head);

	return 0;
}