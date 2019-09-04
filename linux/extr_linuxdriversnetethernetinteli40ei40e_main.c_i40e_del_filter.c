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
typedef  int /*<<< orphan*/  u8 ;
struct i40e_vsi {int dummy; } ;
struct i40e_mac_filter {int dummy; } ;
typedef  int /*<<< orphan*/  s16 ;

/* Variables and functions */
 int /*<<< orphan*/  __i40e_del_filter (struct i40e_vsi*,struct i40e_mac_filter*) ; 
 struct i40e_mac_filter* i40e_find_filter (struct i40e_vsi*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 

void i40e_del_filter(struct i40e_vsi *vsi, const u8 *macaddr, s16 vlan)
{
	struct i40e_mac_filter *f;

	if (!vsi || !macaddr)
		return;

	f = i40e_find_filter(vsi, macaddr, vlan);
	__i40e_del_filter(vsi, f);
}