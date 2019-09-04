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
struct i40e_vsi {scalar_t__ type; } ;
struct i40e_pf {int num_alloc_vsi; struct i40e_vsi** vsi; } ;

/* Variables and functions */

__attribute__((used)) static inline struct i40e_vsi *
i40e_find_vsi_by_type(struct i40e_pf *pf, u16 type)
{
	int i;

	for (i = 0; i < pf->num_alloc_vsi; i++) {
		struct i40e_vsi *vsi = pf->vsi[i];

		if (vsi && vsi->type == type)
			return vsi;
	}

	return NULL;
}