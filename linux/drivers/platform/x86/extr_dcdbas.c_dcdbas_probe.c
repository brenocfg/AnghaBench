#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  kobj; } ;
struct platform_device {TYPE_1__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_BIT_MASK (int) ; 
 int /*<<< orphan*/  DRIVER_DESCRIPTION ; 
 int /*<<< orphan*/  DRIVER_VERSION ; 
 int /*<<< orphan*/  HC_ACTION_NONE ; 
 int /*<<< orphan*/  HC_SMITYPE_NONE ; 
 int /*<<< orphan*/  dcdbas_attr_group ; 
 int dcdbas_check_wsmt () ; 
 struct platform_device* dcdbas_pdev ; 
 int /*<<< orphan*/  dcdbas_reboot_nb ; 
 int /*<<< orphan*/  dev_info (TYPE_1__*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int dma_set_coherent_mask (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  host_control_action ; 
 int /*<<< orphan*/  host_control_smi_type ; 
 int /*<<< orphan*/  register_reboot_notifier (int /*<<< orphan*/ *) ; 
 int sysfs_create_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int dcdbas_probe(struct platform_device *dev)
{
	int error;

	host_control_action = HC_ACTION_NONE;
	host_control_smi_type = HC_SMITYPE_NONE;

	dcdbas_pdev = dev;

	/* Check if ACPI WSMT table specifies protected SMI buffer address */
	error = dcdbas_check_wsmt();
	if (error < 0)
		return error;

	/*
	 * BIOS SMI calls require buffer addresses be in 32-bit address space.
	 * This is done by setting the DMA mask below.
	 */
	error = dma_set_coherent_mask(&dcdbas_pdev->dev, DMA_BIT_MASK(32));
	if (error)
		return error;

	error = sysfs_create_group(&dev->dev.kobj, &dcdbas_attr_group);
	if (error)
		return error;

	register_reboot_notifier(&dcdbas_reboot_nb);

	dev_info(&dev->dev, "%s (version %s)\n",
		 DRIVER_DESCRIPTION, DRIVER_VERSION);

	return 0;
}