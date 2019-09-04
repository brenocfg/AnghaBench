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
typedef  int u8 ;
struct pci_device_id {int dummy; } ;
struct pci_dev {int dummy; } ;
struct ide_port_info {int udma_mask; int /*<<< orphan*/ * port_ops; } ;

/* Variables and functions */
 size_t ATA_133 ; 
 int ENOTSUPP ; 
 size_t chipset_family ; 
 int ide_pci_init_one (struct pci_dev*,struct ide_port_info*,int /*<<< orphan*/ *) ; 
 int pci_enable_device (struct pci_dev*) ; 
 struct ide_port_info sis5513_chipset ; 
 int /*<<< orphan*/  sis_ata133_port_ops ; 
 scalar_t__ sis_find_family (struct pci_dev*) ; 
 int /*<<< orphan*/  sis_port_ops ; 

__attribute__((used)) static int sis5513_init_one(struct pci_dev *dev, const struct pci_device_id *id)
{
	struct ide_port_info d = sis5513_chipset;
	u8 udma_rates[] = { 0x00, 0x00, 0x07, 0x1f, 0x3f, 0x3f, 0x7f, 0x7f };
	int rc;

	rc = pci_enable_device(dev);
	if (rc)
		return rc;

	if (sis_find_family(dev) == 0)
		return -ENOTSUPP;

	if (chipset_family >= ATA_133)
		d.port_ops = &sis_ata133_port_ops;
	else
		d.port_ops = &sis_port_ops;

	d.udma_mask = udma_rates[chipset_family];

	return ide_pci_init_one(dev, &d, NULL);
}