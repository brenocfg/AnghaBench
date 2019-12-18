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
struct TYPE_2__ {char const* name; int /*<<< orphan*/  irq_set_affinity; int /*<<< orphan*/  irq_set_vcpu_affinity; int /*<<< orphan*/  irq_eoi; int /*<<< orphan*/  irq_mask; struct device* parent_device; } ;
struct gic_chip_data {TYPE_1__ chip; } ;
struct device {int dummy; } ;

/* Variables and functions */
 TYPE_1__ gic_chip ; 
 struct gic_chip_data* gic_data ; 
 int /*<<< orphan*/  gic_eoimode1_eoi_irq ; 
 int /*<<< orphan*/  gic_eoimode1_mask_irq ; 
 int /*<<< orphan*/  gic_irq_set_vcpu_affinity ; 
 int /*<<< orphan*/  gic_set_affinity ; 

__attribute__((used)) static void gic_init_chip(struct gic_chip_data *gic, struct device *dev,
			  const char *name, bool use_eoimode1)
{
	/* Initialize irq_chip */
	gic->chip = gic_chip;
	gic->chip.name = name;
	gic->chip.parent_device = dev;

	if (use_eoimode1) {
		gic->chip.irq_mask = gic_eoimode1_mask_irq;
		gic->chip.irq_eoi = gic_eoimode1_eoi_irq;
		gic->chip.irq_set_vcpu_affinity = gic_irq_set_vcpu_affinity;
	}

#ifdef CONFIG_SMP
	if (gic == &gic_data[0])
		gic->chip.irq_set_affinity = gic_set_affinity;
#endif
}