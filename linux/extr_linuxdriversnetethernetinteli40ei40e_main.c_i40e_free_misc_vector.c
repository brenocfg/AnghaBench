#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct i40e_pf {int flags; int /*<<< orphan*/  state; TYPE_1__* msix_entries; int /*<<< orphan*/  hw; } ;
struct TYPE_2__ {int /*<<< orphan*/  vector; } ;

/* Variables and functions */
 int I40E_FLAG_MSIX_ENABLED ; 
 int /*<<< orphan*/  I40E_PFINT_ICR0_ENA ; 
 int /*<<< orphan*/  __I40E_MISC_IRQ_REQUESTED ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct i40e_pf*) ; 
 int /*<<< orphan*/  i40e_flush (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  synchronize_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wr32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void i40e_free_misc_vector(struct i40e_pf *pf)
{
	/* Disable ICR 0 */
	wr32(&pf->hw, I40E_PFINT_ICR0_ENA, 0);
	i40e_flush(&pf->hw);

	if (pf->flags & I40E_FLAG_MSIX_ENABLED && pf->msix_entries) {
		synchronize_irq(pf->msix_entries[0].vector);
		free_irq(pf->msix_entries[0].vector, pf);
		clear_bit(__I40E_MISC_IRQ_REQUESTED, pf->state);
	}
}