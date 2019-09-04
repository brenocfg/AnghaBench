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
typedef  int u8 ;
struct TYPE_3__ {scalar_t__ altstatus_addr; } ;
struct ata_port {TYPE_2__* ops; TYPE_1__ ioaddr; } ;
struct TYPE_4__ {int (* sff_check_status ) (struct ata_port*) ;scalar_t__ sff_check_altstatus; } ;

/* Variables and functions */
 int ATA_BUSY ; 
 int ata_sff_altstatus (struct ata_port*) ; 
 int stub1 (struct ata_port*) ; 

__attribute__((used)) static u8 ata_sff_irq_status(struct ata_port *ap)
{
	u8 status;

	if (ap->ops->sff_check_altstatus || ap->ioaddr.altstatus_addr) {
		status = ata_sff_altstatus(ap);
		/* Not us: We are busy */
		if (status & ATA_BUSY)
			return status;
	}
	/* Clear INTRQ latch */
	status = ap->ops->sff_check_status(ap);
	return status;
}