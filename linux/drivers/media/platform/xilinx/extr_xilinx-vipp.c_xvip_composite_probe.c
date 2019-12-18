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
struct xvip_composite_device {int /*<<< orphan*/ * dev; int /*<<< orphan*/  notifier; int /*<<< orphan*/  dmas; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 struct xvip_composite_device* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct xvip_composite_device*) ; 
 int /*<<< orphan*/  v4l2_async_notifier_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xvip_composite_v4l2_cleanup (struct xvip_composite_device*) ; 
 int xvip_composite_v4l2_init (struct xvip_composite_device*) ; 
 int xvip_graph_init (struct xvip_composite_device*) ; 

__attribute__((used)) static int xvip_composite_probe(struct platform_device *pdev)
{
	struct xvip_composite_device *xdev;
	int ret;

	xdev = devm_kzalloc(&pdev->dev, sizeof(*xdev), GFP_KERNEL);
	if (!xdev)
		return -ENOMEM;

	xdev->dev = &pdev->dev;
	INIT_LIST_HEAD(&xdev->dmas);
	v4l2_async_notifier_init(&xdev->notifier);

	ret = xvip_composite_v4l2_init(xdev);
	if (ret < 0)
		return ret;

	ret = xvip_graph_init(xdev);
	if (ret < 0)
		goto error;

	platform_set_drvdata(pdev, xdev);

	dev_info(xdev->dev, "device registered\n");

	return 0;

error:
	xvip_composite_v4l2_cleanup(xdev);
	return ret;
}