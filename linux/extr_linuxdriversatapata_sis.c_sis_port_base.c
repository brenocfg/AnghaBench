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
struct pci_dev {int dummy; } ;
struct ata_port {int port_no; TYPE_2__* host; } ;
struct ata_device {int devno; TYPE_1__* link; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {struct ata_port* ap; } ;

/* Variables and functions */
 int /*<<< orphan*/  pci_read_config_dword (struct pci_dev*,int,int*) ; 
 struct pci_dev* to_pci_dev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sis_port_base(struct ata_device *adev)
{
	struct ata_port *ap = adev->link->ap;
	struct pci_dev *pdev = to_pci_dev(ap->host->dev);
	int port = 0x40;
	u32 reg54;

	/* If bit 30 is set then the registers are mapped at 0x70 not 0x40 */
	pci_read_config_dword(pdev, 0x54, &reg54);
	if (reg54 & 0x40000000)
		port = 0x70;

	return port + (8 * ap->port_no) + (4 * adev->devno);
}