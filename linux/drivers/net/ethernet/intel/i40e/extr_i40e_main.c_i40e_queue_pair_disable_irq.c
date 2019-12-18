#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct i40e_vsi {int base_vector; struct i40e_pf* back; struct i40e_ring** rx_rings; } ;
struct i40e_ring {TYPE_1__* q_vector; } ;
struct i40e_hw {int dummy; } ;
struct i40e_pf {int flags; TYPE_3__* pdev; TYPE_2__* msix_entries; struct i40e_hw hw; } ;
struct TYPE_6__ {int /*<<< orphan*/  irq; } ;
struct TYPE_5__ {int /*<<< orphan*/  vector; } ;
struct TYPE_4__ {int v_idx; } ;

/* Variables and functions */
 int I40E_FLAG_MSIX_ENABLED ; 
 int /*<<< orphan*/  I40E_PFINT_DYN_CTL0 ; 
 int /*<<< orphan*/  I40E_PFINT_DYN_CTLN (int) ; 
 int /*<<< orphan*/  I40E_PFINT_ICR0_ENA ; 
 int /*<<< orphan*/  i40e_flush (struct i40e_hw*) ; 
 int /*<<< orphan*/  synchronize_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wr32 (struct i40e_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void i40e_queue_pair_disable_irq(struct i40e_vsi *vsi, int queue_pair)
{
	struct i40e_ring *rxr = vsi->rx_rings[queue_pair];
	struct i40e_pf *pf = vsi->back;
	struct i40e_hw *hw = &pf->hw;

	/* For simplicity, instead of removing the qp interrupt causes
	 * from the interrupt linked list, we simply disable the interrupt, and
	 * leave the list intact.
	 *
	 * All rings in a qp belong to the same qvector.
	 */
	if (pf->flags & I40E_FLAG_MSIX_ENABLED) {
		u32 intpf = vsi->base_vector + rxr->q_vector->v_idx;

		wr32(hw, I40E_PFINT_DYN_CTLN(intpf - 1), 0);
		i40e_flush(hw);
		synchronize_irq(pf->msix_entries[intpf].vector);
	} else {
		/* Legacy and MSI mode - this stops all interrupt handling */
		wr32(hw, I40E_PFINT_ICR0_ENA, 0);
		wr32(hw, I40E_PFINT_DYN_CTL0, 0);
		i40e_flush(hw);
		synchronize_irq(pf->pdev->irq);
	}
}