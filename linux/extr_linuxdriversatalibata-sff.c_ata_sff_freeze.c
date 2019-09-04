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
struct TYPE_4__ {scalar_t__ ctl_addr; } ;
struct ata_port {TYPE_1__* ops; int /*<<< orphan*/  ctl; TYPE_2__ ioaddr; int /*<<< orphan*/  last_ctl; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* sff_irq_clear ) (struct ata_port*) ;int /*<<< orphan*/  (* sff_check_status ) (struct ata_port*) ;scalar_t__ sff_set_devctl; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATA_NIEN ; 
 int /*<<< orphan*/  ata_sff_set_devctl (struct ata_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct ata_port*) ; 
 int /*<<< orphan*/  stub2 (struct ata_port*) ; 

void ata_sff_freeze(struct ata_port *ap)
{
	ap->ctl |= ATA_NIEN;
	ap->last_ctl = ap->ctl;

	if (ap->ops->sff_set_devctl || ap->ioaddr.ctl_addr)
		ata_sff_set_devctl(ap, ap->ctl);

	/* Under certain circumstances, some controllers raise IRQ on
	 * ATA_NIEN manipulation.  Also, many controllers fail to mask
	 * previously pending IRQ on ATA_NIEN assertion.  Clear it.
	 */
	ap->ops->sff_check_status(ap);

	if (ap->ops->sff_irq_clear)
		ap->ops->sff_irq_clear(ap);
}