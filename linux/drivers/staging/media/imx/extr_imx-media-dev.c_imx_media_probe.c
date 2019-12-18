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
struct device {struct device_node* of_node; } ;
struct platform_device {struct device dev; } ;
struct imx_media_dev {int /*<<< orphan*/  md; int /*<<< orphan*/  v4l2_dev; int /*<<< orphan*/  notifier; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct imx_media_dev*) ; 
 int PTR_ERR (struct imx_media_dev*) ; 
 int imx_media_add_of_subdevs (struct imx_media_dev*,struct device_node*) ; 
 struct imx_media_dev* imx_media_dev_init (struct device*,int /*<<< orphan*/ *) ; 
 int imx_media_dev_notifier_register (struct imx_media_dev*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  imx_media_notifier_ops ; 
 int /*<<< orphan*/  media_device_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_async_notifier_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_device_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_err (int /*<<< orphan*/ *,char*,int) ; 

__attribute__((used)) static int imx_media_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct device_node *node = dev->of_node;
	struct imx_media_dev *imxmd;
	int ret;

	imxmd = imx_media_dev_init(dev, NULL);
	if (IS_ERR(imxmd))
		return PTR_ERR(imxmd);

	ret = imx_media_add_of_subdevs(imxmd, node);
	if (ret) {
		v4l2_err(&imxmd->v4l2_dev,
			 "add_of_subdevs failed with %d\n", ret);
		goto cleanup;
	}

	ret = imx_media_dev_notifier_register(imxmd, &imx_media_notifier_ops);
	if (ret)
		goto cleanup;

	return 0;

cleanup:
	v4l2_async_notifier_cleanup(&imxmd->notifier);
	v4l2_device_unregister(&imxmd->v4l2_dev);
	media_device_cleanup(&imxmd->md);

	return ret;
}