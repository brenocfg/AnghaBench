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
struct renesas_usb3 {int /*<<< orphan*/  ep0_req; int /*<<< orphan*/  gadget; int /*<<< orphan*/  role_sw; int /*<<< orphan*/  dentry; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  __renesas_usb3_ep_free_request (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugfs_remove_recursive (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_attr_role ; 
 int /*<<< orphan*/  device_remove_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct renesas_usb3* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  pm_runtime_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  renesas_usb3_dma_free_prd (struct renesas_usb3*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_del_gadget_udc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_role_switch_unregister (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int renesas_usb3_remove(struct platform_device *pdev)
{
	struct renesas_usb3 *usb3 = platform_get_drvdata(pdev);

	debugfs_remove_recursive(usb3->dentry);
	device_remove_file(&pdev->dev, &dev_attr_role);

	usb_role_switch_unregister(usb3->role_sw);

	usb_del_gadget_udc(&usb3->gadget);
	renesas_usb3_dma_free_prd(usb3, &pdev->dev);

	__renesas_usb3_ep_free_request(usb3->ep0_req);
	pm_runtime_disable(&pdev->dev);

	return 0;
}