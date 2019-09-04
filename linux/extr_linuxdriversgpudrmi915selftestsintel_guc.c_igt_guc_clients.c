#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct intel_guc {TYPE_2__* preempt_client; TYPE_2__* execbuf_client; } ;
struct TYPE_11__ {int /*<<< orphan*/  struct_mutex; } ;
struct drm_i915_private {TYPE_1__ drm; struct intel_guc guc; } ;
struct TYPE_12__ {int /*<<< orphan*/  priority; int /*<<< orphan*/  stage_id; } ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 int /*<<< orphan*/  GEM_BUG_ON (int) ; 
 int /*<<< orphan*/  GUC_CLIENT_PRIORITY_KMD_HIGH ; 
 int /*<<< orphan*/  GUC_CLIENT_PRIORITY_KMD_NORMAL ; 
 int /*<<< orphan*/  HAS_GUC (struct drm_i915_private*) ; 
 int /*<<< orphan*/  __create_doorbell (TYPE_2__*) ; 
 int /*<<< orphan*/  __destroy_doorbell (TYPE_2__*) ; 
 int __guc_allocate_doorbell (struct intel_guc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  available_dbs (struct intel_guc*,int /*<<< orphan*/ ) ; 
 int check_all_doorbells (struct intel_guc*) ; 
 scalar_t__ client_doorbell_in_sync (TYPE_2__*) ; 
 int create_doorbell (TYPE_2__*) ; 
 int /*<<< orphan*/  destroy_doorbell (TYPE_2__*) ; 
 int guc_clients_create (struct intel_guc*) ; 
 int /*<<< orphan*/  guc_clients_destroy (struct intel_guc*) ; 
 int guc_clients_doorbell_init (struct intel_guc*) ; 
 int /*<<< orphan*/  has_doorbell (TYPE_2__*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 
 int reserve_doorbell (TYPE_2__*) ; 
 int /*<<< orphan*/  unreserve_doorbell (TYPE_2__*) ; 
 int validate_client (TYPE_2__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int igt_guc_clients(void *args)
{
	struct drm_i915_private *dev_priv = args;
	struct intel_guc *guc;
	int err = 0;

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

	/*
	 * Get rid of clients created during driver load because the test will
	 * recreate them.
	 */
	guc_clients_destroy(guc);
	if (guc->execbuf_client || guc->preempt_client) {
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
			      GUC_CLIENT_PRIORITY_KMD_NORMAL, false);
	if (err) {
		pr_err("execbug client validation failed\n");
		goto out;
	}

	if (guc->preempt_client) {
		err = validate_client(guc->preempt_client,
				      GUC_CLIENT_PRIORITY_KMD_HIGH, true);
		if (err) {
			pr_err("preempt client validation failed\n");
			goto out;
		}
	}

	/* each client should now have reserved a doorbell */
	if (!has_doorbell(guc->execbuf_client) ||
	    (guc->preempt_client && !has_doorbell(guc->preempt_client))) {
		pr_err("guc_clients_create didn't reserve doorbells\n");
		err = -EINVAL;
		goto out;
	}

	/* Now create the doorbells */
	guc_clients_doorbell_init(guc);

	/* each client should now have received a doorbell */
	if (!client_doorbell_in_sync(guc->execbuf_client) ||
	    !client_doorbell_in_sync(guc->preempt_client)) {
		pr_err("failed to initialize the doorbells\n");
		err = -EINVAL;
		goto out;
	}

	/*
	 * Basic test - an attempt to reallocate a valid doorbell to the
	 * client it is currently assigned should not cause a failure.
	 */
	err = guc_clients_doorbell_init(guc);
	if (err)
		goto out;

	/*
	 * Negative test - a client with no doorbell (invalid db id).
	 * After destroying the doorbell, the db id is changed to
	 * GUC_DOORBELL_INVALID and the firmware will reject any attempt to
	 * allocate a doorbell with an invalid id (db has to be reserved before
	 * allocation).
	 */
	destroy_doorbell(guc->execbuf_client);
	if (client_doorbell_in_sync(guc->execbuf_client)) {
		pr_err("destroy db did not work\n");
		err = -EINVAL;
		goto out;
	}

	unreserve_doorbell(guc->execbuf_client);

	__create_doorbell(guc->execbuf_client);
	err = __guc_allocate_doorbell(guc, guc->execbuf_client->stage_id);
	if (err != -EIO) {
		pr_err("unexpected (err = %d)", err);
		goto out_db;
	}

	if (!available_dbs(guc, guc->execbuf_client->priority)) {
		pr_err("doorbell not available when it should\n");
		err = -EIO;
		goto out_db;
	}

out_db:
	/* clean after test */
	__destroy_doorbell(guc->execbuf_client);
	err = reserve_doorbell(guc->execbuf_client);
	if (err) {
		pr_err("failed to reserve back the doorbell back\n");
	}
	err = create_doorbell(guc->execbuf_client);
	if (err) {
		pr_err("recreate doorbell failed\n");
		goto out;
	}

out:
	/*
	 * Leave clean state for other test, plus the driver always destroy the
	 * clients during unload.
	 */
	destroy_doorbell(guc->execbuf_client);
	if (guc->preempt_client)
		destroy_doorbell(guc->preempt_client);
	guc_clients_destroy(guc);
	guc_clients_create(guc);
	guc_clients_doorbell_init(guc);
unlock:
	mutex_unlock(&dev_priv->drm.struct_mutex);
	return err;
}