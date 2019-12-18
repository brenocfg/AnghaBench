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
struct vchiq_mmal_port {int /*<<< orphan*/  slock; int /*<<< orphan*/  buffers; } ;
struct vchiq_mmal_instance {int dummy; } ;
struct mmal_buffer {int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int EINVAL ; 
 int buffer_from_host (struct vchiq_mmal_instance*,struct vchiq_mmal_port*,struct mmal_buffer*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int vchiq_mmal_submit_buffer(struct vchiq_mmal_instance *instance,
			     struct vchiq_mmal_port *port,
			     struct mmal_buffer *buffer)
{
	unsigned long flags = 0;
	int ret;

	ret = buffer_from_host(instance, port, buffer);
	if (ret == -EINVAL) {
		/* Port is disabled. Queue for when it is enabled. */
		spin_lock_irqsave(&port->slock, flags);
		list_add_tail(&buffer->list, &port->buffers);
		spin_unlock_irqrestore(&port->slock, flags);
	}

	return 0;
}