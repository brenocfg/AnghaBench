#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct TYPE_3__ {int num_tc; } ;
struct TYPE_4__ {TYPE_1__ qopt; } ;
struct i40e_vsi {TYPE_2__ mqprio_qopt; } ;
struct i40e_pf {size_t lan_vsi; struct i40e_vsi** vsi; } ;

/* Variables and functions */
 int BIT (int) ; 

__attribute__((used)) static u8 i40e_mqprio_get_enabled_tc(struct i40e_pf *pf)
{
	struct i40e_vsi *vsi = pf->vsi[pf->lan_vsi];
	u8 num_tc = vsi->mqprio_qopt.qopt.num_tc;
	u8 enabled_tc = 1, i;

	for (i = 1; i < num_tc; i++)
		enabled_tc |= BIT(i);
	return enabled_tc;
}