#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;
typedef  struct TYPE_12__   TYPE_11__ ;

/* Type definitions */
typedef  scalar_t__ u16 ;
struct intel_guc {int dummy; } ;
struct TYPE_13__ {int /*<<< orphan*/  struct_mutex; } ;
struct drm_i915_private {TYPE_1__ drm; int /*<<< orphan*/  kernel_context; struct intel_guc guc; } ;
struct TYPE_14__ {scalar_t__ stage_id; scalar_t__ doorbell_id; } ;
struct TYPE_12__ {int /*<<< orphan*/  ring_mask; } ;

/* Variables and functions */
 int ATTEMPTS ; 
 int EINVAL ; 
 int ENOSPC ; 
 int /*<<< orphan*/  GEM_BUG_ON (int) ; 
 int GUC_CLIENT_PRIORITY_NUM ; 
 scalar_t__ GUC_NUM_DOORBELLS ; 
 int /*<<< orphan*/  HAS_GUC (struct drm_i915_private*) ; 
 TYPE_11__* INTEL_INFO (struct drm_i915_private*) ; 
 scalar_t__ IS_ERR (TYPE_2__*) ; 
 int /*<<< orphan*/  IS_ERR_OR_NULL (TYPE_2__*) ; 
 int PTR_ERR (TYPE_2__*) ; 
 scalar_t__ available_dbs (struct intel_guc*,int) ; 
 int check_all_doorbells (struct intel_guc*) ; 
 TYPE_2__** clients ; 
 int create_doorbell (TYPE_2__*) ; 
 int /*<<< orphan*/  destroy_doorbell (TYPE_2__*) ; 
 TYPE_2__* guc_client_alloc (struct drm_i915_private*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  guc_client_free (TYPE_2__*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 
 int validate_client (TYPE_2__*,int,int) ; 

__attribute__((used)) static int igt_guc_doorbells(void *arg)
{
	struct drm_i915_private *dev_priv = arg;
	struct intel_guc *guc;
	int i, err = 0;
	u16 db_id;

	GEM_BUG_ON(!HAS_GUC(dev_priv));
	mutex_lock(&dev_priv->drm.struct_mutex);

	guc = &dev_priv->guc;
	if (!guc) {
		pr_err("No guc object!\n");
		err = -EINVAL;
		goto unlock;
	}

	err = check_all_doorbells(guc);
	if (err)
		goto unlock;

	for (i = 0; i < ATTEMPTS; i++) {
		clients[i] = guc_client_alloc(dev_priv,
					      INTEL_INFO(dev_priv)->ring_mask,
					      i % GUC_CLIENT_PRIORITY_NUM,
					      dev_priv->kernel_context);

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

		err = validate_client(clients[i],
				      i % GUC_CLIENT_PRIORITY_NUM, false);
		if (err) {
			pr_err("[%d] client_alloc sanity check failed!\n", i);
			err = -EINVAL;
			goto out;
		}

		db_id = clients[i]->doorbell_id;

		err = create_doorbell(clients[i]);
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
	}

out:
	for (i = 0; i < ATTEMPTS; i++)
		if (!IS_ERR_OR_NULL(clients[i])) {
			destroy_doorbell(clients[i]);
			guc_client_free(clients[i]);
		}
unlock:
	mutex_unlock(&dev_priv->drm.struct_mutex);
	return err;
}