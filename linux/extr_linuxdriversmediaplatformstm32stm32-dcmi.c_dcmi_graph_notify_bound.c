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
struct v4l2_subdev {int /*<<< orphan*/  name; } ;
struct v4l2_async_subdev {int dummy; } ;
struct v4l2_async_notifier {int dummy; } ;
struct TYPE_2__ {struct v4l2_subdev* subdev; } ;
struct stm32_dcmi {TYPE_1__ entity; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 struct stm32_dcmi* notifier_to_dcmi (struct v4l2_async_notifier*) ; 

__attribute__((used)) static int dcmi_graph_notify_bound(struct v4l2_async_notifier *notifier,
				   struct v4l2_subdev *subdev,
				   struct v4l2_async_subdev *asd)
{
	struct stm32_dcmi *dcmi = notifier_to_dcmi(notifier);

	dev_dbg(dcmi->dev, "Subdev %s bound\n", subdev->name);

	dcmi->entity.subdev = subdev;

	return 0;
}