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
typedef  int /*<<< orphan*/  u32 ;
struct mp_chip_data {int /*<<< orphan*/  count; } ;
struct irq_domain {int dummy; } ;
struct irq_alloc_info {int dummy; } ;
struct TYPE_2__ {int srcbusirq; int /*<<< orphan*/  srcbus; } ;

/* Variables and functions */
 int EBUSY ; 
 int ENOENT ; 
 int ENOSYS ; 
 unsigned int IOAPIC_MAP_ALLOC ; 
 int alloc_irq_from_domain (struct irq_domain*,int,int /*<<< orphan*/ ,struct irq_alloc_info*) ; 
 int alloc_isa_irq_from_domain (struct irq_domain*,int,int,int,struct irq_alloc_info*) ; 
 int /*<<< orphan*/  ioapic_copy_alloc_attr (struct irq_alloc_info*,struct irq_alloc_info*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  ioapic_mutex ; 
 int irq_find_mapping (struct irq_domain*,int) ; 
 struct mp_chip_data* irq_get_chip_data (int) ; 
 int /*<<< orphan*/  mp_bus_not_pci ; 
 int /*<<< orphan*/  mp_check_pin_attr (int,struct irq_alloc_info*) ; 
 struct irq_domain* mp_ioapic_irqdomain (int) ; 
 TYPE_1__* mp_irqs ; 
 int mp_is_legacy_irq (int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mp_map_pin_to_irq(u32 gsi, int idx, int ioapic, int pin,
			     unsigned int flags, struct irq_alloc_info *info)
{
	int irq;
	bool legacy = false;
	struct irq_alloc_info tmp;
	struct mp_chip_data *data;
	struct irq_domain *domain = mp_ioapic_irqdomain(ioapic);

	if (!domain)
		return -ENOSYS;

	if (idx >= 0 && test_bit(mp_irqs[idx].srcbus, mp_bus_not_pci)) {
		irq = mp_irqs[idx].srcbusirq;
		legacy = mp_is_legacy_irq(irq);
	}

	mutex_lock(&ioapic_mutex);
	if (!(flags & IOAPIC_MAP_ALLOC)) {
		if (!legacy) {
			irq = irq_find_mapping(domain, pin);
			if (irq == 0)
				irq = -ENOENT;
		}
	} else {
		ioapic_copy_alloc_attr(&tmp, info, gsi, ioapic, pin);
		if (legacy)
			irq = alloc_isa_irq_from_domain(domain, irq,
							ioapic, pin, &tmp);
		else if ((irq = irq_find_mapping(domain, pin)) == 0)
			irq = alloc_irq_from_domain(domain, ioapic, gsi, &tmp);
		else if (!mp_check_pin_attr(irq, &tmp))
			irq = -EBUSY;
		if (irq >= 0) {
			data = irq_get_chip_data(irq);
			data->count++;
		}
	}
	mutex_unlock(&ioapic_mutex);

	return irq;
}