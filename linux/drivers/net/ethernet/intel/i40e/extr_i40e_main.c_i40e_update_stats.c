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
struct i40e_vsi {struct i40e_pf* back; } ;
struct i40e_pf {size_t lan_vsi; struct i40e_vsi** vsi; } ;

/* Variables and functions */
 int /*<<< orphan*/  i40e_update_pf_stats (struct i40e_pf*) ; 
 int /*<<< orphan*/  i40e_update_vsi_stats (struct i40e_vsi*) ; 

void i40e_update_stats(struct i40e_vsi *vsi)
{
	struct i40e_pf *pf = vsi->back;

	if (vsi == pf->vsi[pf->lan_vsi])
		i40e_update_pf_stats(pf);

	i40e_update_vsi_stats(vsi);
}