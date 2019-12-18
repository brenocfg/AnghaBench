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
struct ifx_spi_device {unsigned char power_status; int /*<<< orphan*/  power_lock; TYPE_1__* spi_dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  pm_runtime_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void
ifx_spi_power_state_set(struct ifx_spi_device *ifx_dev, unsigned char val)
{
	unsigned long flags;

	spin_lock_irqsave(&ifx_dev->power_lock, flags);

	/*
	 * if power status is already non-0, just update, else
	 * tell power system
	 */
	if (!ifx_dev->power_status)
		pm_runtime_get(&ifx_dev->spi_dev->dev);
	ifx_dev->power_status |= val;

	spin_unlock_irqrestore(&ifx_dev->power_lock, flags);
}