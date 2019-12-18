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
typedef  int /*<<< orphan*/  u32 ;
struct vchiq_mmal_port {int dummy; } ;
struct vchiq_mmal_instance {int /*<<< orphan*/  vchiq_mutex; } ;

/* Variables and functions */
 int EINTR ; 
 scalar_t__ mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int port_parameter_get (struct vchiq_mmal_instance*,struct vchiq_mmal_port*,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *) ; 

int vchiq_mmal_port_parameter_get(struct vchiq_mmal_instance *instance,
				  struct vchiq_mmal_port *port,
				  u32 parameter, void *value, u32 *value_size)
{
	int ret;

	if (mutex_lock_interruptible(&instance->vchiq_mutex))
		return -EINTR;

	ret = port_parameter_get(instance, port, parameter, value, value_size);

	mutex_unlock(&instance->vchiq_mutex);

	return ret;
}