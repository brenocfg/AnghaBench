#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ice_hw {int dummy; } ;
struct ice_pf {size_t oicr_idx; int num_avail_sw_msix; int /*<<< orphan*/  irq_tracker; TYPE_2__* msix_entries; TYPE_1__* pdev; struct ice_hw hw; } ;
struct TYPE_4__ {int /*<<< orphan*/  vector; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ICE_RES_MISC_VEC_ID ; 
 int /*<<< orphan*/  PFINT_OICR_ENA ; 
 int /*<<< orphan*/  devm_free_irq (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct ice_pf*) ; 
 int /*<<< orphan*/  ice_dis_ctrlq_interrupts (struct ice_hw*) ; 
 int /*<<< orphan*/  ice_flush (struct ice_hw*) ; 
 int /*<<< orphan*/  ice_free_res (int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  synchronize_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wr32 (struct ice_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ice_free_irq_msix_misc(struct ice_pf *pf)
{
	struct ice_hw *hw = &pf->hw;

	ice_dis_ctrlq_interrupts(hw);

	/* disable OICR interrupt */
	wr32(hw, PFINT_OICR_ENA, 0);
	ice_flush(hw);

	if (pf->msix_entries) {
		synchronize_irq(pf->msix_entries[pf->oicr_idx].vector);
		devm_free_irq(&pf->pdev->dev,
			      pf->msix_entries[pf->oicr_idx].vector, pf);
	}

	pf->num_avail_sw_msix += 1;
	ice_free_res(pf->irq_tracker, pf->oicr_idx, ICE_RES_MISC_VEC_ID);
}