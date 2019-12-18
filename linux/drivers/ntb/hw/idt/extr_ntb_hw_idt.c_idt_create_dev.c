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
struct pci_device_id {scalar_t__ driver_data; } ;
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {struct pci_dev* pdev; } ;
struct idt_ntb_dev {struct idt_89hpes_cfg* swcfg; int /*<<< orphan*/  gasa_lock; int /*<<< orphan*/  msg_mask_lock; int /*<<< orphan*/  db_mask_lock; TYPE_1__ ntb; } ;
struct idt_89hpes_cfg {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct idt_ntb_dev* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 struct idt_ntb_dev* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct idt_ntb_dev *idt_create_dev(struct pci_dev *pdev,
					  const struct pci_device_id *id)
{
	struct idt_ntb_dev *ndev;

	/* Allocate memory for the IDT PCIe-device descriptor */
	ndev = devm_kzalloc(&pdev->dev, sizeof(*ndev), GFP_KERNEL);
	if (!ndev) {
		dev_err(&pdev->dev, "Memory allocation failed for descriptor");
		return ERR_PTR(-ENOMEM);
	}

	/* Save the IDT PCIe-switch ports configuration */
	ndev->swcfg = (struct idt_89hpes_cfg *)id->driver_data;
	/* Save the PCI-device pointer inside the NTB device structure */
	ndev->ntb.pdev = pdev;

	/* Initialize spin locker of Doorbell, Message and GASA registers */
	spin_lock_init(&ndev->db_mask_lock);
	spin_lock_init(&ndev->msg_mask_lock);
	spin_lock_init(&ndev->gasa_lock);

	dev_info(&pdev->dev, "IDT %s discovered", ndev->swcfg->name);

	dev_dbg(&pdev->dev, "NTB device descriptor created");

	return ndev;
}