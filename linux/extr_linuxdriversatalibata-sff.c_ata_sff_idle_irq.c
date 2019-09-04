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
struct TYPE_2__ {int /*<<< orphan*/  idle_irq; } ;
struct ata_port {TYPE_1__ stats; } ;

/* Variables and functions */

__attribute__((used)) static unsigned int ata_sff_idle_irq(struct ata_port *ap)
{
	ap->stats.idle_irq++;

#ifdef ATA_IRQ_TRAP
	if ((ap->stats.idle_irq % 1000) == 0) {
		ap->ops->sff_check_status(ap);
		if (ap->ops->sff_irq_clear)
			ap->ops->sff_irq_clear(ap);
		ata_port_warn(ap, "irq trap\n");
		return 1;
	}
#endif
	return 0;	/* irq not handled */
}