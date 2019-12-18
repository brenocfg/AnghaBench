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
struct phy_device {TYPE_1__* drv; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {scalar_t__ (* handle_interrupt ) (struct phy_device*) ;int /*<<< orphan*/  (* did_interrupt ) (struct phy_device*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 scalar_t__ phy_clear_interrupt (struct phy_device*) ; 
 int /*<<< orphan*/  phy_error (struct phy_device*) ; 
 int /*<<< orphan*/  phy_trigger_machine (struct phy_device*) ; 
 int /*<<< orphan*/  stub1 (struct phy_device*) ; 
 scalar_t__ stub2 (struct phy_device*) ; 

__attribute__((used)) static irqreturn_t phy_interrupt(int irq, void *phy_dat)
{
	struct phy_device *phydev = phy_dat;

	if (phydev->drv->did_interrupt && !phydev->drv->did_interrupt(phydev))
		return IRQ_NONE;

	if (phydev->drv->handle_interrupt) {
		if (phydev->drv->handle_interrupt(phydev))
			goto phy_err;
	} else {
		/* reschedule state queue work to run as soon as possible */
		phy_trigger_machine(phydev);
	}

	if (phy_clear_interrupt(phydev))
		goto phy_err;
	return IRQ_HANDLED;

phy_err:
	phy_error(phydev);
	return IRQ_NONE;
}