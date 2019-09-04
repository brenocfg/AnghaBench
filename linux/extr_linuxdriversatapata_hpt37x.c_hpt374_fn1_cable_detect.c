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
typedef  int u16 ;
struct pci_dev {int dummy; } ;
struct ata_port {int port_no; TYPE_1__* host; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ATA_CBL_PATA40 ; 
 int ATA_CBL_PATA80 ; 
 int /*<<< orphan*/  pci_read_config_byte (struct pci_dev*,int,int*) ; 
 int /*<<< orphan*/  pci_read_config_word (struct pci_dev*,unsigned int,int*) ; 
 int /*<<< orphan*/  pci_write_config_word (struct pci_dev*,unsigned int,int) ; 
 struct pci_dev* to_pci_dev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hpt374_fn1_cable_detect(struct ata_port *ap)
{
	struct pci_dev *pdev = to_pci_dev(ap->host->dev);
	unsigned int mcrbase = 0x50 + 4 * ap->port_no;
	u16 mcr3;
	u8 ata66;

	/* Do the extra channel work */
	pci_read_config_word(pdev, mcrbase + 2, &mcr3);
	/* Set bit 15 of 0x52 to enable TCBLID as input */
	pci_write_config_word(pdev, mcrbase + 2, mcr3 | 0x8000);
	pci_read_config_byte(pdev, 0x5A, &ata66);
	/* Reset TCBLID/FCBLID to output */
	pci_write_config_word(pdev, mcrbase + 2, mcr3);

	if (ata66 & (2 >> ap->port_no))
		return ATA_CBL_PATA40;
	else
		return ATA_CBL_PATA80;
}