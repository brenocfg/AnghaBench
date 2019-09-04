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
struct xive_irq_data {int /*<<< orphan*/ * trig_mmio; int /*<<< orphan*/ * eoi_mmio; } ;

/* Variables and functions */
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ *) ; 

void xive_cleanup_irq_data(struct xive_irq_data *xd)
{
	if (xd->eoi_mmio) {
		iounmap(xd->eoi_mmio);
		if (xd->eoi_mmio == xd->trig_mmio)
			xd->trig_mmio = NULL;
		xd->eoi_mmio = NULL;
	}
	if (xd->trig_mmio) {
		iounmap(xd->trig_mmio);
		xd->trig_mmio = NULL;
	}
}