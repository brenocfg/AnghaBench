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
struct n2_cipher_tmpl {char* name; char* drv_name; int /*<<< orphan*/  ablkcipher; int /*<<< orphan*/  enc_type; int /*<<< orphan*/  block_size; } ;
struct n2_cipher_context {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  ablkcipher; } ;
struct crypto_alg {int cra_flags; int cra_ctxsize; int /*<<< orphan*/  cra_name; int /*<<< orphan*/  cra_module; int /*<<< orphan*/  cra_init; TYPE_1__ cra_u; int /*<<< orphan*/ * cra_type; int /*<<< orphan*/  cra_blocksize; int /*<<< orphan*/  cra_priority; int /*<<< orphan*/  cra_driver_name; } ;
struct n2_cipher_alg {int /*<<< orphan*/  entry; int /*<<< orphan*/  enc_type; struct crypto_alg alg; } ;

/* Variables and functions */
 int CRYPTO_ALG_ASYNC ; 
 int CRYPTO_ALG_KERN_DRIVER_ONLY ; 
 int CRYPTO_ALG_TYPE_ABLKCIPHER ; 
 int /*<<< orphan*/  CRYPTO_MAX_ALG_NAME ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  N2_CRA_PRIORITY ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  cipher_algs ; 
 int /*<<< orphan*/  crypto_ablkcipher_type ; 
 int crypto_register_alg (struct crypto_alg*) ; 
 int /*<<< orphan*/  kfree (struct n2_cipher_alg*) ; 
 struct n2_cipher_alg* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  n2_cipher_cra_init ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*) ; 

__attribute__((used)) static int __n2_register_one_cipher(const struct n2_cipher_tmpl *tmpl)
{
	struct n2_cipher_alg *p = kzalloc(sizeof(*p), GFP_KERNEL);
	struct crypto_alg *alg;
	int err;

	if (!p)
		return -ENOMEM;

	alg = &p->alg;

	snprintf(alg->cra_name, CRYPTO_MAX_ALG_NAME, "%s", tmpl->name);
	snprintf(alg->cra_driver_name, CRYPTO_MAX_ALG_NAME, "%s-n2", tmpl->drv_name);
	alg->cra_priority = N2_CRA_PRIORITY;
	alg->cra_flags = CRYPTO_ALG_TYPE_ABLKCIPHER |
			 CRYPTO_ALG_KERN_DRIVER_ONLY | CRYPTO_ALG_ASYNC;
	alg->cra_blocksize = tmpl->block_size;
	p->enc_type = tmpl->enc_type;
	alg->cra_ctxsize = sizeof(struct n2_cipher_context);
	alg->cra_type = &crypto_ablkcipher_type;
	alg->cra_u.ablkcipher = tmpl->ablkcipher;
	alg->cra_init = n2_cipher_cra_init;
	alg->cra_module = THIS_MODULE;

	list_add(&p->entry, &cipher_algs);
	err = crypto_register_alg(alg);
	if (err) {
		pr_err("%s alg registration failed\n", alg->cra_name);
		list_del(&p->entry);
		kfree(p);
	} else {
		pr_info("%s alg registered\n", alg->cra_name);
	}
	return err;
}