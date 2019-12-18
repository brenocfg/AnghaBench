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
struct phy_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IP101A_G_IRQ_CONF_STATUS ; 
 int IP101A_G_IRQ_DUPLEX_CHANGE ; 
 int IP101A_G_IRQ_LINK_CHANGE ; 
 int IP101A_G_IRQ_SPEED_CHANGE ; 
 int phy_read (struct phy_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ip101a_g_did_interrupt(struct phy_device *phydev)
{
	int val = phy_read(phydev, IP101A_G_IRQ_CONF_STATUS);

	if (val < 0)
		return 0;

	return val & (IP101A_G_IRQ_SPEED_CHANGE |
		      IP101A_G_IRQ_DUPLEX_CHANGE |
		      IP101A_G_IRQ_LINK_CHANGE);
}