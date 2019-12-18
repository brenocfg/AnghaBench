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
 int i40e_up_complete (struct i40e_vsi*) ; 
 int i40e_vsi_configure (struct i40e_vsi*) ; 

int i40e_up(struct i40e_vsi *vsi)
{
	int err;

	err = i40e_vsi_configure(vsi);
	if (!err)
		err = i40e_up_complete(vsi);

	return err;
}