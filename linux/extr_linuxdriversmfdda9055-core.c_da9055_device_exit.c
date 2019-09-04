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
struct da9055 {int /*<<< orphan*/  dev; int /*<<< orphan*/  irq_data; int /*<<< orphan*/  chip_irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  mfd_remove_devices (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regmap_del_irq_chip (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void da9055_device_exit(struct da9055 *da9055)
{
	regmap_del_irq_chip(da9055->chip_irq, da9055->irq_data);
	mfd_remove_devices(da9055->dev);
}