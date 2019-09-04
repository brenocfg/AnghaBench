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
struct i40e_pf {int num_alloc_vsi; scalar_t__* vsi; } ;

/* Variables and functions */
 int /*<<< orphan*/  i40e_quiesce_vsi (scalar_t__) ; 

__attribute__((used)) static void i40e_pf_quiesce_all_vsi(struct i40e_pf *pf)
{
	int v;

	for (v = 0; v < pf->num_alloc_vsi; v++) {
		if (pf->vsi[v])
			i40e_quiesce_vsi(pf->vsi[v]);
	}
}