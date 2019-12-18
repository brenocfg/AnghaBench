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
struct pci_device_id {int dummy; } ;
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct idt_ntb_dev {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR_OR_NULL (struct idt_ntb_dev*) ; 
 int PTR_ERR (struct idt_ntb_dev*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 int idt_check_setup (struct pci_dev*) ; 
 struct idt_ntb_dev* idt_create_dev (struct pci_dev*,struct pci_device_id const*) ; 
 int /*<<< orphan*/  idt_deinit_isr (struct idt_ntb_dev*) ; 
 int /*<<< orphan*/  idt_deinit_link (struct idt_ntb_dev*) ; 
 int /*<<< orphan*/  idt_deinit_pci (struct idt_ntb_dev*) ; 
 int /*<<< orphan*/  idt_init_dbgfs (struct idt_ntb_dev*) ; 
 int idt_init_isr (struct idt_ntb_dev*) ; 
 int /*<<< orphan*/  idt_init_link (struct idt_ntb_dev*) ; 
 int /*<<< orphan*/  idt_init_msg (struct idt_ntb_dev*) ; 
 int idt_init_mws (struct idt_ntb_dev*) ; 
 int idt_init_pci (struct idt_ntb_dev*) ; 
 int /*<<< orphan*/  idt_init_temp (struct idt_ntb_dev*) ; 
 int idt_register_device (struct idt_ntb_dev*) ; 
 int /*<<< orphan*/  idt_scan_ports (struct idt_ntb_dev*) ; 

__attribute__((used)) static int idt_pci_probe(struct pci_dev *pdev,
			 const struct pci_device_id *id)
{
	struct idt_ntb_dev *ndev;
	int ret;

	/* Check whether IDT PCIe-switch is properly pre-initialized */
	ret = idt_check_setup(pdev);
	if (ret != 0)
		return ret;

	/* Allocate the memory for IDT NTB device data */
	ndev = idt_create_dev(pdev, id);
	if (IS_ERR_OR_NULL(ndev))
		return PTR_ERR(ndev);

	/* Initialize the basic PCI subsystem of the device */
	ret = idt_init_pci(ndev);
	if (ret != 0)
		return ret;

	/* Scan ports of the IDT PCIe-switch */
	(void)idt_scan_ports(ndev);

	/* Initialize NTB link events subsystem */
	idt_init_link(ndev);

	/* Initialize MWs subsystem */
	ret = idt_init_mws(ndev);
	if (ret != 0)
		goto err_deinit_link;

	/* Initialize Messaging subsystem */
	idt_init_msg(ndev);

	/* Initialize hwmon interface */
	idt_init_temp(ndev);

	/* Initialize IDT interrupts handler */
	ret = idt_init_isr(ndev);
	if (ret != 0)
		goto err_deinit_link;

	/* Register IDT NTB devices on the NTB bus */
	ret = idt_register_device(ndev);
	if (ret != 0)
		goto err_deinit_isr;

	/* Initialize DebugFS info node */
	(void)idt_init_dbgfs(ndev);

	/* IDT PCIe-switch NTB driver is finally initialized */
	dev_info(&pdev->dev, "IDT NTB device is ready");

	/* May the force be with us... */
	return 0;

err_deinit_isr:
	idt_deinit_isr(ndev);
err_deinit_link:
	idt_deinit_link(ndev);
	idt_deinit_pci(ndev);

	return ret;
}