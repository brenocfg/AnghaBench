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
struct i40e_vsi {int num_q_vectors; struct i40e_pf* back; } ;
struct i40e_pf {int flags; int /*<<< orphan*/  hw; } ;

/* Variables and functions */
 int I40E_FLAG_MSIX_ENABLED ; 
 int /*<<< orphan*/  i40e_flush (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i40e_irq_dynamic_enable (struct i40e_vsi*,int) ; 
 int /*<<< orphan*/  i40e_irq_dynamic_enable_icr0 (struct i40e_pf*) ; 

__attribute__((used)) static int i40e_vsi_enable_irq(struct i40e_vsi *vsi)
{
	struct i40e_pf *pf = vsi->back;
	int i;

	if (pf->flags & I40E_FLAG_MSIX_ENABLED) {
		for (i = 0; i < vsi->num_q_vectors; i++)
			i40e_irq_dynamic_enable(vsi, i);
	} else {
		i40e_irq_dynamic_enable_icr0(pf);
	}

	i40e_flush(&pf->hw);
	return 0;
}