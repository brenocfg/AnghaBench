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
struct ice_pf {int num_avail_sw_msix; int oicr_idx; int /*<<< orphan*/  irq_tracker; int /*<<< orphan*/ * int_name; TYPE_2__* pdev; TYPE_1__* msix_entries; int /*<<< orphan*/  state; struct ice_hw hw; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  vector; } ;

/* Variables and functions */
 int /*<<< orphan*/  GLINT_ITR (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  ICE_ITR_8K ; 
 int ICE_ITR_GRAN_S ; 
 int /*<<< orphan*/  ICE_RES_MISC_VEC_ID ; 
 int /*<<< orphan*/  ICE_RX_ITR ; 
 int ITR_REG_ALIGN (int /*<<< orphan*/ ) ; 
 char* dev_driver_string (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int) ; 
 char* dev_name (int /*<<< orphan*/ *) ; 
 int devm_request_irq (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct ice_pf*) ; 
 int /*<<< orphan*/  ice_ena_ctrlq_interrupts (struct ice_hw*,size_t) ; 
 int /*<<< orphan*/  ice_ena_misc_vector (struct ice_pf*) ; 
 int /*<<< orphan*/  ice_flush (struct ice_hw*) ; 
 int /*<<< orphan*/  ice_free_res (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int ice_get_res (struct ice_pf*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ice_irq_dynamic_ena (struct ice_hw*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ ice_is_reset_in_progress (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ice_misc_intr ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ *,int,char*,char*,char*) ; 
 int /*<<< orphan*/  wr32 (struct ice_hw*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ice_req_irq_msix_misc(struct ice_pf *pf)
{
	struct ice_hw *hw = &pf->hw;
	int oicr_idx, err = 0;

	if (!pf->int_name[0])
		snprintf(pf->int_name, sizeof(pf->int_name) - 1, "%s-%s:misc",
			 dev_driver_string(&pf->pdev->dev),
			 dev_name(&pf->pdev->dev));

	/* Do not request IRQ but do enable OICR interrupt since settings are
	 * lost during reset. Note that this function is called only during
	 * rebuild path and not while reset is in progress.
	 */
	if (ice_is_reset_in_progress(pf->state))
		goto skip_req_irq;

	/* reserve one vector in irq_tracker for misc interrupts */
	oicr_idx = ice_get_res(pf, pf->irq_tracker, 1, ICE_RES_MISC_VEC_ID);
	if (oicr_idx < 0)
		return oicr_idx;

	pf->num_avail_sw_msix -= 1;
	pf->oicr_idx = oicr_idx;

	err = devm_request_irq(&pf->pdev->dev,
			       pf->msix_entries[pf->oicr_idx].vector,
			       ice_misc_intr, 0, pf->int_name, pf);
	if (err) {
		dev_err(&pf->pdev->dev,
			"devm_request_irq for %s failed: %d\n",
			pf->int_name, err);
		ice_free_res(pf->irq_tracker, 1, ICE_RES_MISC_VEC_ID);
		pf->num_avail_sw_msix += 1;
		return err;
	}

skip_req_irq:
	ice_ena_misc_vector(pf);

	ice_ena_ctrlq_interrupts(hw, pf->oicr_idx);
	wr32(hw, GLINT_ITR(ICE_RX_ITR, pf->oicr_idx),
	     ITR_REG_ALIGN(ICE_ITR_8K) >> ICE_ITR_GRAN_S);

	ice_flush(hw);
	ice_irq_dynamic_ena(hw, NULL, NULL);

	return 0;
}