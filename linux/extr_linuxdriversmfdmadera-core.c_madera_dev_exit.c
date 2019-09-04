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
struct madera {int /*<<< orphan*/  core_supplies; int /*<<< orphan*/  num_core_supplies; int /*<<< orphan*/  dev; int /*<<< orphan*/  dcvdd; int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  disable_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  madera_enable_hard_reset (struct madera*) ; 
 int /*<<< orphan*/  mfd_remove_devices (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regulator_bulk_disable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regulator_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regulator_put (int /*<<< orphan*/ ) ; 

int madera_dev_exit(struct madera *madera)
{
	/* Prevent any IRQs being serviced while we clean up */
	disable_irq(madera->irq);

	/*
	 * DCVDD could be supplied by a child node, we must disable it before
	 * removing the children, and prevent PM runtime from turning it back on
	 */
	pm_runtime_disable(madera->dev);

	regulator_disable(madera->dcvdd);
	regulator_put(madera->dcvdd);

	mfd_remove_devices(madera->dev);
	madera_enable_hard_reset(madera);

	regulator_bulk_disable(madera->num_core_supplies,
			       madera->core_supplies);
	return 0;
}