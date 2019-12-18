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
struct vchiq_mmal_instance {int /*<<< orphan*/  vchiq_mutex; } ;
struct vchiq_mmal_component {int enabled; } ;

/* Variables and functions */
 int EINTR ; 
 int enable_component (struct vchiq_mmal_instance*,struct vchiq_mmal_component*) ; 
 scalar_t__ mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int vchiq_mmal_component_enable(struct vchiq_mmal_instance *instance,
				struct vchiq_mmal_component *component)
{
	int ret;

	if (mutex_lock_interruptible(&instance->vchiq_mutex))
		return -EINTR;

	if (component->enabled) {
		mutex_unlock(&instance->vchiq_mutex);
		return 0;
	}

	ret = enable_component(instance, component);
	if (ret == 0)
		component->enabled = true;

	mutex_unlock(&instance->vchiq_mutex);

	return ret;
}