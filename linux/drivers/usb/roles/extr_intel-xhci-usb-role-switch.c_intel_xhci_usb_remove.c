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
struct platform_device {int /*<<< orphan*/  dev; } ;
struct intel_xhci_usb_data {int /*<<< orphan*/  role_sw; } ;

/* Variables and functions */
 int /*<<< orphan*/  fwnode_handle_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_xhci_usb_node ; 
 struct intel_xhci_usb_data* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  pm_runtime_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  software_node_fwnode (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_role_switch_unregister (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int intel_xhci_usb_remove(struct platform_device *pdev)
{
	struct intel_xhci_usb_data *data = platform_get_drvdata(pdev);

	pm_runtime_disable(&pdev->dev);

	usb_role_switch_unregister(data->role_sw);
	fwnode_handle_put(software_node_fwnode(&intel_xhci_usb_node));

	return 0;
}