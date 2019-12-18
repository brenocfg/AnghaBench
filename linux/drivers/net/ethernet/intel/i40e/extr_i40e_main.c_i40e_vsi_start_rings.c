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
struct i40e_vsi {int dummy; } ;

/* Variables and functions */
 int i40e_vsi_control_rx (struct i40e_vsi*,int) ; 
 int i40e_vsi_control_tx (struct i40e_vsi*,int) ; 

int i40e_vsi_start_rings(struct i40e_vsi *vsi)
{
	int ret = 0;

	/* do rx first for enable and last for disable */
	ret = i40e_vsi_control_rx(vsi, true);
	if (ret)
		return ret;
	ret = i40e_vsi_control_tx(vsi, true);

	return ret;
}