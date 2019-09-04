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
struct realtek_smi {scalar_t__ vlan4k_enabled; } ;

/* Variables and functions */
 int RTL8366RB_NUM_VIDS ; 
 unsigned int RTL8366RB_NUM_VLANS ; 

__attribute__((used)) static bool rtl8366rb_is_vlan_valid(struct realtek_smi *smi, unsigned int vlan)
{
	unsigned int max = RTL8366RB_NUM_VLANS;

	if (smi->vlan4k_enabled)
		max = RTL8366RB_NUM_VIDS - 1;

	if (vlan == 0 || vlan >= max)
		return false;

	return true;
}