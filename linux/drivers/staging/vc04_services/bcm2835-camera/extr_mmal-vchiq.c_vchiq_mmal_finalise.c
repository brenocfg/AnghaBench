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
struct vchiq_mmal_instance {int /*<<< orphan*/  context_map; int /*<<< orphan*/  bulk_scratch; int /*<<< orphan*/  bulk_wq; int /*<<< orphan*/  vchiq_mutex; int /*<<< orphan*/  handle; } ;

/* Variables and functions */
 int EINTR ; 
 int EINVAL ; 
 int /*<<< orphan*/  destroy_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flush_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  idr_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct vchiq_mmal_instance*) ; 
 scalar_t__ mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int vchi_service_close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vchi_service_use (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfree (int /*<<< orphan*/ ) ; 

int vchiq_mmal_finalise(struct vchiq_mmal_instance *instance)
{
	int status = 0;

	if (!instance)
		return -EINVAL;

	if (mutex_lock_interruptible(&instance->vchiq_mutex))
		return -EINTR;

	vchi_service_use(instance->handle);

	status = vchi_service_close(instance->handle);
	if (status != 0)
		pr_err("mmal-vchiq: VCHIQ close failed\n");

	mutex_unlock(&instance->vchiq_mutex);

	flush_workqueue(instance->bulk_wq);
	destroy_workqueue(instance->bulk_wq);

	vfree(instance->bulk_scratch);

	idr_destroy(&instance->context_map);

	kfree(instance);

	return status;
}