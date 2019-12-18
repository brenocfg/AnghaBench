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
struct TYPE_2__ {scalar_t__ pvid; } ;
struct i40e_vsi {TYPE_1__ info; } ;

/* Variables and functions */
 int /*<<< orphan*/  i40e_vlan_stripping_disable (struct i40e_vsi*) ; 

void i40e_vsi_remove_pvid(struct i40e_vsi *vsi)
{
	vsi->info.pvid = 0;

	i40e_vlan_stripping_disable(vsi);
}