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
struct tegra_mipi_device {TYPE_1__* mipi; } ;
struct TYPE_2__ {scalar_t__ usage_count; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int tegra_mipi_power_down (TYPE_1__*) ; 

int tegra_mipi_disable(struct tegra_mipi_device *dev)
{
	int err = 0;

	mutex_lock(&dev->mipi->lock);

	if (--dev->mipi->usage_count == 0)
		err = tegra_mipi_power_down(dev->mipi);

	mutex_unlock(&dev->mipi->lock);

	return err;

}