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
struct intel_guc {scalar_t__ execbuf_client; } ;
struct TYPE_6__ {int /*<<< orphan*/  struct_mutex; } ;
struct TYPE_4__ {struct intel_guc guc; } ;
struct TYPE_5__ {TYPE_1__ uc; } ;
struct drm_i915_private {TYPE_3__ drm; int /*<<< orphan*/  runtime_pm; TYPE_2__ gt; } ;
typedef  int /*<<< orphan*/  intel_wakeref_t ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  GEM_BUG_ON (int) ; 
 int /*<<< orphan*/  GUC_CLIENT_PRIORITY_KMD_NORMAL ; 
 int /*<<< orphan*/  HAS_GT_UC (struct drm_i915_private*) ; 
 int check_all_doorbells (struct intel_guc*) ; 
 int /*<<< orphan*/  client_doorbell_in_sync (scalar_t__) ; 
 int create_doorbell (scalar_t__) ; 
 int guc_clients_create (struct intel_guc*) ; 
 int /*<<< orphan*/  guc_clients_destroy (struct intel_guc*) ; 
 int /*<<< orphan*/  guc_clients_disable (struct intel_guc*) ; 
 int /*<<< orphan*/  guc_clients_enable (struct intel_guc*) ; 
 int /*<<< orphan*/  has_doorbell (scalar_t__) ; 
 int /*<<< orphan*/  intel_runtime_pm_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  intel_runtime_pm_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int validate_client (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int igt_guc_clients(void *args)
{
	struct drm_i915_private *dev_priv = args;
	intel_wakeref_t wakeref;
	struct intel_guc *guc;
	int err = 0;

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

	/*
	 * Get rid of clients created during driver load because the test will
	 * recreate them.
	 */
	guc_clients_disable(guc);
	guc_clients_destroy(guc);
	if (guc->execbuf_client) {
		pr_err("guc_clients_destroy lied!\n");
		err = -EINVAL;
		goto unlock;
	}

	err = guc_clients_create(guc);
	if (err) {
		pr_err("Failed to create clients\n");
		goto unlock;
	}
	GEM_BUG_ON(!guc->execbuf_client);

	err = validate_client(guc->execbuf_client,
			      GUC_CLIENT_PRIORITY_KMD_NORMAL);
	if (err) {
		pr_err("execbug client validation failed\n");
		goto out;
	}

	/* the client should now have reserved a doorbell */
	if (!has_doorbell(guc->execbuf_client)) {
		pr_err("guc_clients_create didn't reserve doorbells\n");
		err = -EINVAL;
		goto out;
	}

	/* Now enable the clients */
	guc_clients_enable(guc);

	/* each client should now have received a doorbell */
	if (!client_doorbell_in_sync(guc->execbuf_client)) {
		pr_err("failed to initialize the doorbells\n");
		err = -EINVAL;
		goto out;
	}

	/*
	 * Basic test - an attempt to reallocate a valid doorbell to the
	 * client it is currently assigned should not cause a failure.
	 */
	err = create_doorbell(guc->execbuf_client);

out:
	/*
	 * Leave clean state for other test, plus the driver always destroy the
	 * clients during unload.
	 */
	guc_clients_disable(guc);
	guc_clients_destroy(guc);
	guc_clients_create(guc);
	guc_clients_enable(guc);
unlock:
	intel_runtime_pm_put(&dev_priv->runtime_pm, wakeref);
	mutex_unlock(&dev_priv->drm.struct_mutex);
	return err;
}