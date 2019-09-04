#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct pci_dev {int device; } ;
struct ata_link {int pmp; TYPE_2__* ap; } ;
struct TYPE_4__ {int port_no; TYPE_1__* host; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
#define  SCR_CONTROL 129 
#define  SCR_ERROR 128 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  pci_write_config_byte (struct pci_dev*,int,int) ; 
 int /*<<< orphan*/  pci_write_config_dword (struct pci_dev*,int,int) ; 
 struct pci_dev* to_pci_dev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vt8251_scr_write(struct ata_link *link, unsigned int scr, u32 val)
{
	struct pci_dev *pdev = to_pci_dev(link->ap->host->dev);
	int slot = 2 * link->ap->port_no + link->pmp;
	u32 v = 0;

	switch (scr) {
	case SCR_ERROR:
		/* devices other than 5287 uses 0xA8 as base */
		WARN_ON(pdev->device != 0x5287);
		pci_write_config_dword(pdev, 0xB0 + slot * 4, val);
		return 0;

	case SCR_CONTROL:
		/* set the DET field */
		v |= ((val & 0x4) >> 1) | (val & 0x1);

		/* set the IPM field */
		v |= ((val >> 8) & 0x3) << 2;

		pci_write_config_byte(pdev, 0xA4 + slot, v);
		return 0;

	default:
		return -EINVAL;
	}
}