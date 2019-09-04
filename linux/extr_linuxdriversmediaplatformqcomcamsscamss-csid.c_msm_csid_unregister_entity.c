#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  entity; } ;
struct csid_device {int /*<<< orphan*/  ctrls; TYPE_1__ subdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  media_entity_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_ctrl_handler_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_device_unregister_subdev (TYPE_1__*) ; 

void msm_csid_unregister_entity(struct csid_device *csid)
{
	v4l2_device_unregister_subdev(&csid->subdev);
	media_entity_cleanup(&csid->subdev.entity);
	v4l2_ctrl_handler_free(&csid->ctrls);
}