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
struct TYPE_2__ {int /*<<< orphan*/  bmdma_addr; } ;
struct ata_port {int port_no; TYPE_1__ ioaddr; } ;

/* Variables and functions */
 int ATA_CBL_PATA40 ; 
 int ATA_CBL_PATA80 ; 
 int ATA_CBL_SATA ; 
 int /*<<< orphan*/  BUG () ; 
 int ioread8 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int marvell_cable_detect(struct ata_port *ap)
{
	/* Cable type */
	switch(ap->port_no)
	{
	case 0:
		if (ioread8(ap->ioaddr.bmdma_addr + 1) & 1)
			return ATA_CBL_PATA40;
		return ATA_CBL_PATA80;
	case 1: /* Legacy SATA port */
		return ATA_CBL_SATA;
	}

	BUG();
	return 0;	/* Our BUG macro needs the right markup */
}