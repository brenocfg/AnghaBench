#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct list_head {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  ivsize; } ;
struct crypto_alg {int /*<<< orphan*/  cra_name; TYPE_1__ cra_ablkcipher; int /*<<< orphan*/  cra_blocksize; int /*<<< orphan*/  cra_driver_name; } ;
struct ccp_crypto_ablkcipher_alg {int /*<<< orphan*/  entry; struct crypto_alg alg; int /*<<< orphan*/  mode; } ;
struct ccp_aes_def {char* name; char* driver_name; int /*<<< orphan*/  ivsize; int /*<<< orphan*/  blocksize; struct crypto_alg* alg_defaults; int /*<<< orphan*/  mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPTO_MAX_ALG_NAME ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int crypto_register_alg (struct crypto_alg*) ; 
 int /*<<< orphan*/  kfree (struct ccp_crypto_ablkcipher_alg*) ; 
 struct ccp_crypto_ablkcipher_alg* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,struct list_head*) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*) ; 

__attribute__((used)) static int ccp_register_aes_alg(struct list_head *head,
				const struct ccp_aes_def *def)
{
	struct ccp_crypto_ablkcipher_alg *ccp_alg;
	struct crypto_alg *alg;
	int ret;

	ccp_alg = kzalloc(sizeof(*ccp_alg), GFP_KERNEL);
	if (!ccp_alg)
		return -ENOMEM;

	INIT_LIST_HEAD(&ccp_alg->entry);

	ccp_alg->mode = def->mode;

	/* Copy the defaults and override as necessary */
	alg = &ccp_alg->alg;
	*alg = *def->alg_defaults;
	snprintf(alg->cra_name, CRYPTO_MAX_ALG_NAME, "%s", def->name);
	snprintf(alg->cra_driver_name, CRYPTO_MAX_ALG_NAME, "%s",
		 def->driver_name);
	alg->cra_blocksize = def->blocksize;
	alg->cra_ablkcipher.ivsize = def->ivsize;

	ret = crypto_register_alg(alg);
	if (ret) {
		pr_err("%s ablkcipher algorithm registration error (%d)\n",
		       alg->cra_name, ret);
		kfree(ccp_alg);
		return ret;
	}

	list_add(&ccp_alg->entry, head);

	return 0;
}