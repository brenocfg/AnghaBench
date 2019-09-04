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
struct ata_ioports {int /*<<< orphan*/  lbal_addr; int /*<<< orphan*/  nsect_addr; } ;
struct ata_port {int /*<<< orphan*/  host; struct ata_ioports ioaddr; } ;

/* Variables and functions */
 int ata_inb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ata_outb (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pata_s3c_dev_select (struct ata_port*,unsigned int) ; 

__attribute__((used)) static unsigned int pata_s3c_devchk(struct ata_port *ap,
				unsigned int device)
{
	struct ata_ioports *ioaddr = &ap->ioaddr;
	u8 nsect, lbal;

	pata_s3c_dev_select(ap, device);

	ata_outb(ap->host, 0x55, ioaddr->nsect_addr);
	ata_outb(ap->host, 0xaa, ioaddr->lbal_addr);

	ata_outb(ap->host, 0xaa, ioaddr->nsect_addr);
	ata_outb(ap->host, 0x55, ioaddr->lbal_addr);

	ata_outb(ap->host, 0x55, ioaddr->nsect_addr);
	ata_outb(ap->host, 0xaa, ioaddr->lbal_addr);

	nsect = ata_inb(ap->host, ioaddr->nsect_addr);
	lbal = ata_inb(ap->host, ioaddr->lbal_addr);

	if ((nsect == 0x55) && (lbal == 0xaa))
		return 1;	/* we found a device */

	return 0;		/* nothing found */
}