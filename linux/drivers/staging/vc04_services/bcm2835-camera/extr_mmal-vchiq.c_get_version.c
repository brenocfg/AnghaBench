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
typedef  int /*<<< orphan*/  u32 ;
struct vchiq_mmal_instance {int dummy; } ;
struct vchi_held_msg {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  minor; int /*<<< orphan*/  major; } ;
struct TYPE_5__ {TYPE_1__ version; } ;
struct TYPE_6__ {scalar_t__ type; } ;
struct mmal_msg {TYPE_2__ u; TYPE_3__ h; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ MMAL_MSG_TYPE_GET_VERSION ; 
 int send_synchronous_mmal_msg (struct vchiq_mmal_instance*,struct mmal_msg*,int,struct mmal_msg**,struct vchi_held_msg*) ; 
 int /*<<< orphan*/  vchi_held_msg_release (struct vchi_held_msg*) ; 

__attribute__((used)) static int get_version(struct vchiq_mmal_instance *instance,
		       u32 *major_out, u32 *minor_out)
{
	int ret;
	struct mmal_msg m;
	struct mmal_msg *rmsg;
	struct vchi_held_msg rmsg_handle;

	m.h.type = MMAL_MSG_TYPE_GET_VERSION;

	ret = send_synchronous_mmal_msg(instance, &m,
					sizeof(m.u.version),
					&rmsg, &rmsg_handle);
	if (ret)
		return ret;

	if (rmsg->h.type != m.h.type) {
		/* got an unexpected message type in reply */
		ret = -EINVAL;
		goto release_msg;
	}

	*major_out = rmsg->u.version.major;
	*minor_out = rmsg->u.version.minor;

release_msg:
	vchi_held_msg_release(&rmsg_handle);

	return ret;
}