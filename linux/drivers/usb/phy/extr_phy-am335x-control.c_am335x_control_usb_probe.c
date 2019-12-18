#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct resource {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  of_node; } ;
struct platform_device {TYPE_1__ dev; } ;
struct phy_control {int dummy; } ;
struct of_device_id {struct phy_control* data; } ;
struct am335x_control_usb {TYPE_1__* dev; struct phy_control phy_ctrl; int /*<<< orphan*/  lock; void* wkup; void* phy_reg; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (void*) ; 
 int PTR_ERR (void*) ; 
 int /*<<< orphan*/  dev_set_drvdata (TYPE_1__*,struct am335x_control_usb*) ; 
 void* devm_ioremap_resource (TYPE_1__*,struct resource*) ; 
 struct am335x_control_usb* devm_kzalloc (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 struct of_device_id* of_match_node (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  omap_control_usb_id_table ; 
 struct resource* platform_get_resource_byname (struct platform_device*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int am335x_control_usb_probe(struct platform_device *pdev)
{
	struct resource	*res;
	struct am335x_control_usb *ctrl_usb;
	const struct of_device_id *of_id;
	const struct phy_control *phy_ctrl;

	of_id = of_match_node(omap_control_usb_id_table, pdev->dev.of_node);
	if (!of_id)
		return -EINVAL;

	phy_ctrl = of_id->data;

	ctrl_usb = devm_kzalloc(&pdev->dev, sizeof(*ctrl_usb), GFP_KERNEL);
	if (!ctrl_usb)
		return -ENOMEM;

	ctrl_usb->dev = &pdev->dev;

	res = platform_get_resource_byname(pdev, IORESOURCE_MEM, "phy_ctrl");
	ctrl_usb->phy_reg = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(ctrl_usb->phy_reg))
		return PTR_ERR(ctrl_usb->phy_reg);

	res = platform_get_resource_byname(pdev, IORESOURCE_MEM, "wakeup");
	ctrl_usb->wkup = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(ctrl_usb->wkup))
		return PTR_ERR(ctrl_usb->wkup);

	spin_lock_init(&ctrl_usb->lock);
	ctrl_usb->phy_ctrl = *phy_ctrl;

	dev_set_drvdata(ctrl_usb->dev, ctrl_usb);
	return 0;
}