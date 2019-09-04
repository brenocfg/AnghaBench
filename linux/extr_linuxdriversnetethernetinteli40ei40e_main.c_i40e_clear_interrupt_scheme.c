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
struct i40e_pf {int num_alloc_vsi; scalar_t__* vsi; int /*<<< orphan*/  irq_pile; int /*<<< orphan*/  iwarp_base_vector; } ;

/* Variables and functions */
 scalar_t__ I40E_IWARP_IRQ_PILE_ID ; 
 scalar_t__ I40E_PILE_VALID_BIT ; 
 int /*<<< orphan*/  i40e_free_misc_vector (struct i40e_pf*) ; 
 int /*<<< orphan*/  i40e_put_lump (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  i40e_reset_interrupt_capability (struct i40e_pf*) ; 
 int /*<<< orphan*/  i40e_vsi_free_q_vectors (scalar_t__) ; 

__attribute__((used)) static void i40e_clear_interrupt_scheme(struct i40e_pf *pf)
{
	int i;

	i40e_free_misc_vector(pf);

	i40e_put_lump(pf->irq_pile, pf->iwarp_base_vector,
		      I40E_IWARP_IRQ_PILE_ID);

	i40e_put_lump(pf->irq_pile, 0, I40E_PILE_VALID_BIT-1);
	for (i = 0; i < pf->num_alloc_vsi; i++)
		if (pf->vsi[i])
			i40e_vsi_free_q_vectors(pf->vsi[i]);
	i40e_reset_interrupt_capability(pf);
}