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
struct v4l2_async_notifier_operations {int dummy; } ;
struct TYPE_2__ {struct v4l2_async_notifier_operations const* ops; int /*<<< orphan*/  asd_list; } ;
struct imx_media_dev {int /*<<< orphan*/  v4l2_dev; TYPE_1__ notifier; } ;

/* Variables and functions */
 int ENODEV ; 
 struct v4l2_async_notifier_operations const imx_media_notifier_ops ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int v4l2_async_notifier_register (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  v4l2_err (int /*<<< orphan*/ *,char*,...) ; 

int imx_media_dev_notifier_register(struct imx_media_dev *imxmd,
			    const struct v4l2_async_notifier_operations *ops)
{
	int ret;

	/* no subdevs? just bail */
	if (list_empty(&imxmd->notifier.asd_list)) {
		v4l2_err(&imxmd->v4l2_dev, "no subdevs\n");
		return -ENODEV;
	}

	/* prepare the async subdev notifier and register it */
	imxmd->notifier.ops = ops ? ops : &imx_media_notifier_ops;
	ret = v4l2_async_notifier_register(&imxmd->v4l2_dev,
					   &imxmd->notifier);
	if (ret) {
		v4l2_err(&imxmd->v4l2_dev,
			 "v4l2_async_notifier_register failed with %d\n", ret);
		return ret;
	}

	return 0;
}