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
typedef  scalar_t__ uint8_t ;
struct pci_dev {TYPE_1__* bus; } ;
struct ath79_pci_irq {scalar_t__ bus; scalar_t__ slot; scalar_t__ pin; int irq; } ;
struct TYPE_2__ {scalar_t__ number; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct ath79_pci_irq*) ; 
 struct ath79_pci_irq* ar71xx_pci_irq_map ; 
 struct ath79_pci_irq* ar724x_pci_irq_map ; 
 struct ath79_pci_irq* ath79_pci_irq_map ; 
 int ath79_pci_nr_irqs ; 
 int /*<<< orphan*/  pci_name (struct pci_dev*) ; 
 int /*<<< orphan*/  pr_crit (char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ,int,scalar_t__) ; 
 struct ath79_pci_irq* qca955x_pci_irq_map ; 
 scalar_t__ soc_is_ar71xx () ; 
 scalar_t__ soc_is_ar724x () ; 
 scalar_t__ soc_is_ar9342 () ; 
 scalar_t__ soc_is_ar9344 () ; 
 scalar_t__ soc_is_qca955x () ; 

int pcibios_map_irq(const struct pci_dev *dev, uint8_t slot, uint8_t pin)
{
	int irq = -1;
	int i;

	if (ath79_pci_nr_irqs == 0 ||
	    ath79_pci_irq_map == NULL) {
		if (soc_is_ar71xx()) {
			ath79_pci_irq_map = ar71xx_pci_irq_map;
			ath79_pci_nr_irqs = ARRAY_SIZE(ar71xx_pci_irq_map);
		} else if (soc_is_ar724x() ||
			   soc_is_ar9342() ||
			   soc_is_ar9344()) {
			ath79_pci_irq_map = ar724x_pci_irq_map;
			ath79_pci_nr_irqs = ARRAY_SIZE(ar724x_pci_irq_map);
		} else if (soc_is_qca955x()) {
			ath79_pci_irq_map = qca955x_pci_irq_map;
			ath79_pci_nr_irqs = ARRAY_SIZE(qca955x_pci_irq_map);
		} else {
			pr_crit("pci %s: invalid irq map\n",
				pci_name((struct pci_dev *) dev));
			return irq;
		}
	}

	for (i = 0; i < ath79_pci_nr_irqs; i++) {
		const struct ath79_pci_irq *entry;

		entry = &ath79_pci_irq_map[i];
		if (entry->bus == dev->bus->number &&
		    entry->slot == slot &&
		    entry->pin == pin) {
			irq = entry->irq;
			break;
		}
	}

	if (irq < 0)
		pr_crit("pci %s: no irq found for pin %u\n",
			pci_name((struct pci_dev *) dev), pin);
	else
		pr_info("pci %s: using irq %d for pin %u\n",
			pci_name((struct pci_dev *) dev), irq, pin);

	return irq;
}