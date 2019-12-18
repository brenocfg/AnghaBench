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
struct ak7375_device {TYPE_1__ sd; int /*<<< orphan*/  ctrls_vcm; } ;

/* Variables and functions */
 int /*<<< orphan*/  media_entity_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_async_unregister_subdev (TYPE_1__*) ; 
 int /*<<< orphan*/  v4l2_ctrl_handler_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ak7375_subdev_cleanup(struct ak7375_device *ak7375_dev)
{
	v4l2_async_unregister_subdev(&ak7375_dev->sd);
	v4l2_ctrl_handler_free(&ak7375_dev->ctrls_vcm);
	media_entity_cleanup(&ak7375_dev->sd.entity);
}