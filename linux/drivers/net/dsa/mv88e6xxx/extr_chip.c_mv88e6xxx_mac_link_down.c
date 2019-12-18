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
struct dsa_switch {int dummy; } ;
typedef  int /*<<< orphan*/  phy_interface_t ;

/* Variables and functions */
 int /*<<< orphan*/  LINK_FORCED_DOWN ; 
 unsigned int MLO_AN_FIXED ; 
 int /*<<< orphan*/  mv88e6xxx_mac_link_force (struct dsa_switch*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mv88e6xxx_mac_link_down(struct dsa_switch *ds, int port,
				    unsigned int mode,
				    phy_interface_t interface)
{
	if (mode == MLO_AN_FIXED)
		mv88e6xxx_mac_link_force(ds, port, LINK_FORCED_DOWN);
}