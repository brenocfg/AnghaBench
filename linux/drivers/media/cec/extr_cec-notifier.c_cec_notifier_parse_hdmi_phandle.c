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
struct device {int /*<<< orphan*/  of_node; } ;
struct platform_device {struct device dev; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENODEV ; 
 int /*<<< orphan*/  EPROBE_DEFER ; 
 struct device* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 struct platform_device* of_find_device_by_node (struct device_node*) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 struct device_node* of_parse_phandle (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_device (struct device*) ; 

struct device *cec_notifier_parse_hdmi_phandle(struct device *dev)
{
	struct platform_device *hdmi_pdev;
	struct device *hdmi_dev = NULL;
	struct device_node *np;

	np = of_parse_phandle(dev->of_node, "hdmi-phandle", 0);

	if (!np) {
		dev_err(dev, "Failed to find HDMI node in device tree\n");
		return ERR_PTR(-ENODEV);
	}
	hdmi_pdev = of_find_device_by_node(np);
	of_node_put(np);
	if (hdmi_pdev) {
		hdmi_dev = &hdmi_pdev->dev;
		/*
		 * Note that the device struct is only used as a key into the
		 * cec_notifiers list, it is never actually accessed.
		 * So we decrement the reference here so we don't leak
		 * memory.
		 */
		put_device(hdmi_dev);
		return hdmi_dev;
	}
	return ERR_PTR(-EPROBE_DEFER);
}