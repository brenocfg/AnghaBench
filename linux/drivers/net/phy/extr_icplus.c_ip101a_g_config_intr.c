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
typedef  int /*<<< orphan*/  u16 ;
struct phy_device {scalar_t__ interrupts; } ;

/* Variables and functions */
 int /*<<< orphan*/  IP101A_G_IRQ_ALL_MASK ; 
 int /*<<< orphan*/  IP101A_G_IRQ_CONF_STATUS ; 
 int /*<<< orphan*/  IP101A_G_IRQ_PIN_USED ; 
 scalar_t__ PHY_INTERRUPT_ENABLED ; 
 int phy_write (struct phy_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ip101a_g_config_intr(struct phy_device *phydev)
{
	u16 val;

	if (phydev->interrupts == PHY_INTERRUPT_ENABLED)
		/* INTR pin used: Speed/link/duplex will cause an interrupt */
		val = IP101A_G_IRQ_PIN_USED;
	else
		val = IP101A_G_IRQ_ALL_MASK;

	return phy_write(phydev, IP101A_G_IRQ_CONF_STATUS, val);
}