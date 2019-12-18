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
struct ice_vsi {int dummy; } ;

/* Variables and functions */
 int ice_up_complete (struct ice_vsi*) ; 
 int ice_vsi_cfg (struct ice_vsi*) ; 

int ice_up(struct ice_vsi *vsi)
{
	int err;

	err = ice_vsi_cfg(vsi);
	if (!err)
		err = ice_up_complete(vsi);

	return err;
}