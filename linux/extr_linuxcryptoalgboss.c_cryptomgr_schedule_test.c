#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int u32 ;
struct task_struct {int dummy; } ;
struct crypto_test_param {int type; int /*<<< orphan*/  alg; int /*<<< orphan*/  driver; } ;
struct crypto_alg {int cra_flags; int /*<<< orphan*/  cra_name; int /*<<< orphan*/  cra_driver_name; } ;

/* Variables and functions */
 int CRYPTO_ALG_INTERNAL ; 
 int CRYPTO_ALG_TESTED ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct task_struct*) ; 
 int NOTIFY_OK ; 
 int NOTIFY_STOP ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  cryptomgr_test ; 
 int /*<<< orphan*/  kfree (struct crypto_test_param*) ; 
 struct task_struct* kthread_run (int /*<<< orphan*/ ,struct crypto_test_param*,char*) ; 
 struct crypto_test_param* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  try_module_get (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cryptomgr_schedule_test(struct crypto_alg *alg)
{
	struct task_struct *thread;
	struct crypto_test_param *param;
	u32 type;

	if (!try_module_get(THIS_MODULE))
		goto err;

	param = kzalloc(sizeof(*param), GFP_KERNEL);
	if (!param)
		goto err_put_module;

	memcpy(param->driver, alg->cra_driver_name, sizeof(param->driver));
	memcpy(param->alg, alg->cra_name, sizeof(param->alg));
	type = alg->cra_flags;

	/* Do not test internal algorithms. */
	if (type & CRYPTO_ALG_INTERNAL)
		type |= CRYPTO_ALG_TESTED;

	param->type = type;

	thread = kthread_run(cryptomgr_test, param, "cryptomgr_test");
	if (IS_ERR(thread))
		goto err_free_param;

	return NOTIFY_STOP;

err_free_param:
	kfree(param);
err_put_module:
	module_put(THIS_MODULE);
err:
	return NOTIFY_OK;
}