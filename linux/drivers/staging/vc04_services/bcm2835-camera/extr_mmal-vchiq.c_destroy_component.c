#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct vchiq_mmal_instance {int dummy; } ;
struct vchiq_mmal_component {int /*<<< orphan*/  handle; } ;
struct vchi_held_msg {int dummy; } ;
struct TYPE_5__ {int status; } ;
struct TYPE_7__ {int /*<<< orphan*/  component_handle; } ;
struct TYPE_8__ {TYPE_1__ component_destroy_reply; TYPE_3__ component_destroy; } ;
struct TYPE_6__ {scalar_t__ type; } ;
struct mmal_msg {TYPE_4__ u; TYPE_2__ h; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ MMAL_MSG_TYPE_COMPONENT_DESTROY ; 
 int send_synchronous_mmal_msg (struct vchiq_mmal_instance*,struct mmal_msg*,int,struct mmal_msg**,struct vchi_held_msg*) ; 
 int /*<<< orphan*/  vchi_held_msg_release (struct vchi_held_msg*) ; 

__attribute__((used)) static int destroy_component(struct vchiq_mmal_instance *instance,
			     struct vchiq_mmal_component *component)
{
	int ret;
	struct mmal_msg m;
	struct mmal_msg *rmsg;
	struct vchi_held_msg rmsg_handle;

	m.h.type = MMAL_MSG_TYPE_COMPONENT_DESTROY;
	m.u.component_destroy.component_handle = component->handle;

	ret = send_synchronous_mmal_msg(instance, &m,
					sizeof(m.u.component_destroy),
					&rmsg, &rmsg_handle);
	if (ret)
		return ret;

	if (rmsg->h.type != m.h.type) {
		/* got an unexpected message type in reply */
		ret = -EINVAL;
		goto release_msg;
	}

	ret = -rmsg->u.component_destroy_reply.status;

release_msg:

	vchi_held_msg_release(&rmsg_handle);

	return ret;
}