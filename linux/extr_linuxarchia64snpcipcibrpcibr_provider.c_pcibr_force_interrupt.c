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
struct sn_irq_info {int irq_int_bit; scalar_t__ irq_pciioinfo; int /*<<< orphan*/  irq_bridge; } ;
struct pcidev_info {TYPE_1__* pdi_host_pcidev_info; } ;
struct pcibus_info {int dummy; } ;
struct TYPE_2__ {scalar_t__ pdi_pcibus_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  pcireg_force_intr_set (struct pcibus_info*,int) ; 

void pcibr_force_interrupt(struct sn_irq_info *sn_irq_info)
{
	struct pcidev_info *pcidev_info;
	struct pcibus_info *pcibus_info;
	int bit = sn_irq_info->irq_int_bit;

	if (! sn_irq_info->irq_bridge)
		return;

	pcidev_info = (struct pcidev_info *)sn_irq_info->irq_pciioinfo;
	if (pcidev_info) {
		pcibus_info =
		    (struct pcibus_info *)pcidev_info->pdi_host_pcidev_info->
		    pdi_pcibus_info;
		pcireg_force_intr_set(pcibus_info, bit);
	}
}