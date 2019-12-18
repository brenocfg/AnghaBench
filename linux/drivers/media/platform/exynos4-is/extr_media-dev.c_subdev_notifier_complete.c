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
struct v4l2_async_notifier {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  graph_mutex; } ;
struct fimc_md {TYPE_1__ media_dev; int /*<<< orphan*/  v4l2_dev; } ;

/* Variables and functions */
 int fimc_md_create_links (struct fimc_md*) ; 
 int media_device_register (TYPE_1__*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct fimc_md* notifier_to_fimc_md (struct v4l2_async_notifier*) ; 
 int v4l2_device_register_subdev_nodes (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int subdev_notifier_complete(struct v4l2_async_notifier *notifier)
{
	struct fimc_md *fmd = notifier_to_fimc_md(notifier);
	int ret;

	mutex_lock(&fmd->media_dev.graph_mutex);

	ret = fimc_md_create_links(fmd);
	if (ret < 0)
		goto unlock;

	ret = v4l2_device_register_subdev_nodes(&fmd->v4l2_dev);
unlock:
	mutex_unlock(&fmd->media_dev.graph_mutex);
	if (ret < 0)
		return ret;

	return media_device_register(&fmd->media_dev);
}