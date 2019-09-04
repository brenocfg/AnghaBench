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
typedef  int u8 ;
struct pci_dev {int dummy; } ;
struct ata_port {int port_no; TYPE_1__* host; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ATA_CBL_PATA40 ; 
 int ATA_CBL_PATA40_SHORT ; 
 int ATA_CBL_PATA80 ; 
 scalar_t__ ali_cable_override (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_read_config_byte (struct pci_dev*,int,int*) ; 
 struct pci_dev* to_pci_dev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ali_c2_cable_detect(struct ata_port *ap)
{
	struct pci_dev *pdev = to_pci_dev(ap->host->dev);
	u8 ata66;

	/* Certain laptops use short but suitable cables and don't
	   implement the detect logic */

	if (ali_cable_override(pdev))
		return ATA_CBL_PATA40_SHORT;

	/* Host view cable detect 0x4A bit 0 primary bit 1 secondary
	   Bit set for 40 pin */
	pci_read_config_byte(pdev, 0x4A, &ata66);
	if (ata66 & (1 << ap->port_no))
		return ATA_CBL_PATA40;
	else
		return ATA_CBL_PATA80;
}