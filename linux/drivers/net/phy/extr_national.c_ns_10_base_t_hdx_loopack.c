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
typedef  int u16 ;
struct phy_device {int dummy; } ;

/* Variables and functions */
 int BIT (int) ; 
 int ns_exp_read (struct phy_device*,int) ; 
 int /*<<< orphan*/  ns_exp_write (struct phy_device*,int,int) ; 
 int /*<<< orphan*/  pr_debug (char*,char*) ; 

__attribute__((used)) static void ns_10_base_t_hdx_loopack(struct phy_device *phydev, int disable)
{
	u16 lb_dis = BIT(1);

	if (disable)
		ns_exp_write(phydev, 0x1c0,
			     ns_exp_read(phydev, 0x1c0) | lb_dis);
	else
		ns_exp_write(phydev, 0x1c0,
			     ns_exp_read(phydev, 0x1c0) & ~lb_dis);

	pr_debug("10BASE-T HDX loopback %s\n",
		 (ns_exp_read(phydev, 0x1c0) & lb_dis) ? "off" : "on");
}