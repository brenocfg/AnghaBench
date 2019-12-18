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
struct phy_device {void* irq; } ;

/* Variables and functions */
 int IRQF_ONESHOT ; 
 int IRQF_SHARED ; 
 void* PHY_POLL ; 
 scalar_t__ phy_enable_interrupts (struct phy_device*) ; 
 int /*<<< orphan*/  phy_free_interrupt (struct phy_device*) ; 
 int /*<<< orphan*/  phy_interrupt ; 
 int /*<<< orphan*/  phydev_name (struct phy_device*) ; 
 int /*<<< orphan*/  phydev_warn (struct phy_device*,char*,...) ; 
 int request_threaded_irq (void*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct phy_device*) ; 

void phy_request_interrupt(struct phy_device *phydev)
{
	int err;

	err = request_threaded_irq(phydev->irq, NULL, phy_interrupt,
				   IRQF_ONESHOT | IRQF_SHARED,
				   phydev_name(phydev), phydev);
	if (err) {
		phydev_warn(phydev, "Error %d requesting IRQ %d, falling back to polling\n",
			    err, phydev->irq);
		phydev->irq = PHY_POLL;
	} else {
		if (phy_enable_interrupts(phydev)) {
			phydev_warn(phydev, "Can't enable interrupt, falling back to polling\n");
			phy_free_interrupt(phydev);
			phydev->irq = PHY_POLL;
		}
	}
}