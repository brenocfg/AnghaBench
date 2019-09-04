#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct i40e_vsi {int base_vector; int num_queue_pairs; int num_q_vectors; TYPE_3__** xdp_rings; TYPE_2__** rx_rings; TYPE_1__** tx_rings; struct i40e_pf* back; } ;
struct i40e_hw {int dummy; } ;
struct i40e_pf {int flags; TYPE_5__* pdev; TYPE_4__* msix_entries; struct i40e_hw hw; } ;
struct TYPE_10__ {int /*<<< orphan*/  irq; } ;
struct TYPE_9__ {int /*<<< orphan*/  vector; } ;
struct TYPE_8__ {int /*<<< orphan*/  reg_idx; } ;
struct TYPE_7__ {int /*<<< orphan*/  reg_idx; } ;
struct TYPE_6__ {int /*<<< orphan*/  reg_idx; } ;

/* Variables and functions */
 int I40E_FLAG_MSIX_ENABLED ; 
 int /*<<< orphan*/  I40E_PFINT_DYN_CTL0 ; 
 int /*<<< orphan*/  I40E_PFINT_DYN_CTLN (int) ; 
 int /*<<< orphan*/  I40E_PFINT_ICR0_ENA ; 
 int /*<<< orphan*/  I40E_QINT_RQCTL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I40E_QINT_RQCTL_CAUSE_ENA_MASK ; 
 int /*<<< orphan*/  I40E_QINT_TQCTL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I40E_QINT_TQCTL_CAUSE_ENA_MASK ; 
 int /*<<< orphan*/  i40e_enabled_xdp_vsi (struct i40e_vsi*) ; 
 int /*<<< orphan*/  i40e_flush (struct i40e_hw*) ; 
 int /*<<< orphan*/  rd32 (struct i40e_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  synchronize_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wr32 (struct i40e_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void i40e_vsi_disable_irq(struct i40e_vsi *vsi)
{
	struct i40e_pf *pf = vsi->back;
	struct i40e_hw *hw = &pf->hw;
	int base = vsi->base_vector;
	int i;

	/* disable interrupt causation from each queue */
	for (i = 0; i < vsi->num_queue_pairs; i++) {
		u32 val;

		val = rd32(hw, I40E_QINT_TQCTL(vsi->tx_rings[i]->reg_idx));
		val &= ~I40E_QINT_TQCTL_CAUSE_ENA_MASK;
		wr32(hw, I40E_QINT_TQCTL(vsi->tx_rings[i]->reg_idx), val);

		val = rd32(hw, I40E_QINT_RQCTL(vsi->rx_rings[i]->reg_idx));
		val &= ~I40E_QINT_RQCTL_CAUSE_ENA_MASK;
		wr32(hw, I40E_QINT_RQCTL(vsi->rx_rings[i]->reg_idx), val);

		if (!i40e_enabled_xdp_vsi(vsi))
			continue;
		wr32(hw, I40E_QINT_TQCTL(vsi->xdp_rings[i]->reg_idx), 0);
	}

	/* disable each interrupt */
	if (pf->flags & I40E_FLAG_MSIX_ENABLED) {
		for (i = vsi->base_vector;
		     i < (vsi->num_q_vectors + vsi->base_vector); i++)
			wr32(hw, I40E_PFINT_DYN_CTLN(i - 1), 0);

		i40e_flush(hw);
		for (i = 0; i < vsi->num_q_vectors; i++)
			synchronize_irq(pf->msix_entries[i + base].vector);
	} else {
		/* Legacy and MSI mode - this stops all interrupt handling */
		wr32(hw, I40E_PFINT_ICR0_ENA, 0);
		wr32(hw, I40E_PFINT_DYN_CTL0, 0);
		i40e_flush(hw);
		synchronize_irq(pf->pdev->irq);
	}
}