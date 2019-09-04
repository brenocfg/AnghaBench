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
struct switchdev_obj_port_vlan {int dummy; } ;
struct dsa_switch {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static int
mt7530_port_vlan_prepare(struct dsa_switch *ds, int port,
			 const struct switchdev_obj_port_vlan *vlan)
{
	/* nothing needed */

	return 0;
}