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
struct da9052 {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  da9052_irq_exit (struct da9052*) ; 
 int /*<<< orphan*/  mfd_remove_devices (int /*<<< orphan*/ ) ; 

void da9052_device_exit(struct da9052 *da9052)
{
	mfd_remove_devices(da9052->dev);
	da9052_irq_exit(da9052);
}