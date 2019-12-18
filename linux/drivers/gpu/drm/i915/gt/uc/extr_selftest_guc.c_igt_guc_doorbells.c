#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u16 ;
struct intel_guc {int dummy; } ;
struct TYPE_16__ {int /*<<< orphan*/  struct_mutex; } ;
struct TYPE_14__ {struct intel_guc guc; } ;
struct TYPE_15__ {TYPE_1__ uc; } ;
struct drm_i915_private {TYPE_3__ drm; int /*<<< orphan*/  runtime_pm; TYPE_2__ gt; } ;
typedef  int /*<<< orphan*/  intel_wakeref_t ;
struct TYPE_17__ {scalar_t__ stage_id; scalar_t__ doorbell_id; } ;

/* Variables and functions */
 int ATTEMPTS ; 
 int EINVAL ; 
 int ENOSPC ; 
 int /*<<< orphan*/  GEM_BUG_ON (int) ; 
 int GUC_CLIENT_PRIORITY_NUM ; 
 scalar_t__ GUC_NUM_DOORBELLS ; 
 int /*<<< orphan*/  HAS_GT_UC (struct drm_i915_private*) ; 
 scalar_t__ IS_ERR (TYPE_4__*) ; 
 int /*<<< orphan*/  IS_ERR_OR_NULL (TYPE_4__*) ; 
 int PTR_ERR (TYPE_4__*) ; 
 int /*<<< orphan*/  __guc_client_disable (TYPE_4__*) ; 
 int __guc_client_enable (TYPE_4__*) ; 
 scalar_t__ available_dbs (struct intel_guc*,int) ; 
 int check_all_doorbells (struct intel_guc*) ; 
 TYPE_4__** clients ; 
 TYPE_4__* guc_client_alloc (struct intel_guc*,int) ; 
 int /*<<< orphan*/  guc_client_free (TYPE_4__*) ; 
 int /*<<< orphan*/  intel_runtime_pm_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  intel_runtime_pm_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 
 int ring_doorbell_nop (TYPE_4__*) ; 
 int validate_client (TYPE_4__*,int) ; 

__attribute__((used)) static int igt_guc_doorbells(void *arg)
{
	struct drm_i915_private *dev_priv = arg;
	intel_wakeref_t wakeref;
	struct intel_guc *guc;
	int i, err = 0;
	u16 db_id;

	GEM_BUG_ON(!HAS_GT_UC(dev_priv));
	mutex_lock(&dev_priv->drm.struct_mutex);
	wakeref = intel_runtime_pm_get(&dev_priv->runtime_pm);

	guc = &dev_priv->gt.uc.guc;
	if (!guc) {
		pr_err("No guc object!\n");
		err = -EINVAL;
		goto unlock;
	}

	err = check_all_doorbells(guc);
	if (err)
		goto unlock;

	for (i = 0; i < ATTEMPTS; i++) {
		clients[i] = guc_client_alloc(guc, i % GUC_CLIENT_PRIORITY_NUM);

		if (!clients[i]) {
			pr_err("[%d] No guc client\n", i);
			err = -EINVAL;
			goto out;
		}

		if (IS_ERR(clients[i])) {
			if (PTR_ERR(clients[i]) != -ENOSPC) {
				pr_err("[%d] unexpected error\n", i);
				err = PTR_ERR(clients[i]);
				goto out;
			}

			if (available_dbs(guc, i % GUC_CLIENT_PRIORITY_NUM)) {
				pr_err("[%d] non-db related alloc fail\n", i);
				err = -EINVAL;
				goto out;
			}

			/* expected, ran out of dbs for this client type */
			continue;
		}

		/*
		 * The check below is only valid because we keep a doorbell
		 * assigned during the whole life of the client.
		 */
		if (clients[i]->stage_id >= GUC_NUM_DOORBELLS) {
			pr_err("[%d] more clients than doorbells (%d >= %d)\n",
			       i, clients[i]->stage_id, GUC_NUM_DOORBELLS);
			err = -EINVAL;
			goto out;
		}

		err = validate_client(clients[i], i % GUC_CLIENT_PRIORITY_NUM);
		if (err) {
			pr_err("[%d] client_alloc sanity check failed!\n", i);
			err = -EINVAL;
			goto out;
		}

		db_id = clients[i]->doorbell_id;

		err = __guc_client_enable(clients[i]);
		if (err) {
			pr_err("[%d] Failed to create a doorbell\n", i);
			goto out;
		}

		/* doorbell id shouldn't change, we are holding the mutex */
		if (db_id != clients[i]->doorbell_id) {
			pr_err("[%d] doorbell id changed (%d != %d)\n",
			       i, db_id, clients[i]->doorbell_id);
			err = -EINVAL;
			goto out;
		}

		err = check_all_doorbells(guc);
		if (err)
			goto out;

		err = ring_doorbell_nop(clients[i]);
		if (err)
			goto out;
	}

out:
	for (i = 0; i < ATTEMPTS; i++)
		if (!IS_ERR_OR_NULL(clients[i])) {
			__guc_client_disable(clients[i]);
			guc_client_free(clients[i]);
		}
unlock:
	intel_runtime_pm_put(&dev_priv->runtime_pm, wakeref);
	mutex_unlock(&dev_priv->drm.struct_mutex);
	return err;
}