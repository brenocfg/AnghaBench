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
typedef  scalar_t__ u16 ;
struct i40e_vsi {scalar_t__ id; } ;
struct i40e_pf {int num_alloc_vsi; struct i40e_vsi** vsi; } ;

/* Variables and functions */

struct i40e_vsi *i40e_find_vsi_from_id(struct i40e_pf *pf, u16 id)
{
	int i;

	for (i = 0; i < pf->num_alloc_vsi; i++)
		if (pf->vsi[i] && (pf->vsi[i]->id == id))
			return pf->vsi[i];

	return NULL;
}