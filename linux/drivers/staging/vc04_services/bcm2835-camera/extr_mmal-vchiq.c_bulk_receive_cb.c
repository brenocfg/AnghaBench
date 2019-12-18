#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct vchiq_mmal_instance {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  work; scalar_t__ status; } ;
struct TYPE_4__ {TYPE_1__ bulk; } ;
struct mmal_msg_context {TYPE_2__ u; } ;

/* Variables and functions */
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void bulk_receive_cb(struct vchiq_mmal_instance *instance,
			    struct mmal_msg_context *msg_context)
{
	msg_context->u.bulk.status = 0;

	/* schedule the port callback */
	schedule_work(&msg_context->u.bulk.work);
}