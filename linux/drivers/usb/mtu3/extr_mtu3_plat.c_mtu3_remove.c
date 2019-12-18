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
struct ssusb_mtk {int dr_mode; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
#define  USB_DR_MODE_HOST 130 
#define  USB_DR_MODE_OTG 129 
#define  USB_DR_MODE_PERIPHERAL 128 
 struct ssusb_mtk* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  pm_runtime_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_put_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ssusb_debugfs_remove_root (struct ssusb_mtk*) ; 
 int /*<<< orphan*/  ssusb_gadget_exit (struct ssusb_mtk*) ; 
 int /*<<< orphan*/  ssusb_host_exit (struct ssusb_mtk*) ; 
 int /*<<< orphan*/  ssusb_otg_switch_exit (struct ssusb_mtk*) ; 
 int /*<<< orphan*/  ssusb_rscs_exit (struct ssusb_mtk*) ; 

__attribute__((used)) static int mtu3_remove(struct platform_device *pdev)
{
	struct ssusb_mtk *ssusb = platform_get_drvdata(pdev);

	switch (ssusb->dr_mode) {
	case USB_DR_MODE_PERIPHERAL:
		ssusb_gadget_exit(ssusb);
		break;
	case USB_DR_MODE_HOST:
		ssusb_host_exit(ssusb);
		break;
	case USB_DR_MODE_OTG:
		ssusb_otg_switch_exit(ssusb);
		ssusb_gadget_exit(ssusb);
		ssusb_host_exit(ssusb);
		break;
	default:
		return -EINVAL;
	}

	ssusb_rscs_exit(ssusb);
	pm_runtime_put_sync(&pdev->dev);
	pm_runtime_disable(&pdev->dev);
	ssusb_debugfs_remove_root(ssusb);

	return 0;
}