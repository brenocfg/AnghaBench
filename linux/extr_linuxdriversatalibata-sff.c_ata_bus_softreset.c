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
struct ata_ioports {scalar_t__ ctl_addr; } ;
struct ata_port {int ctl; int last_ctl; int /*<<< orphan*/  link; struct ata_ioports ioaddr; int /*<<< orphan*/  print_id; } ;

/* Variables and functions */
 int ATA_SRST ; 
 int /*<<< orphan*/  DPRINTK (char*,int /*<<< orphan*/ ) ; 
 int ata_sff_wait_after_reset (int /*<<< orphan*/ *,unsigned int,unsigned long) ; 
 int /*<<< orphan*/  iowrite8 (int,scalar_t__) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int ata_bus_softreset(struct ata_port *ap, unsigned int devmask,
			     unsigned long deadline)
{
	struct ata_ioports *ioaddr = &ap->ioaddr;

	DPRINTK("ata%u: bus reset via SRST\n", ap->print_id);

	if (ap->ioaddr.ctl_addr) {
		/* software reset.  causes dev0 to be selected */
		iowrite8(ap->ctl, ioaddr->ctl_addr);
		udelay(20);	/* FIXME: flush */
		iowrite8(ap->ctl | ATA_SRST, ioaddr->ctl_addr);
		udelay(20);	/* FIXME: flush */
		iowrite8(ap->ctl, ioaddr->ctl_addr);
		ap->last_ctl = ap->ctl;
	}

	/* wait the port to become ready */
	return ata_sff_wait_after_reset(&ap->link, devmask, deadline);
}