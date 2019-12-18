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
typedef  int u8 ;
typedef  int u32 ;
typedef  int u16 ;
struct ice_vf {scalar_t__ num_mdd_events; } ;
struct ice_hw {int dummy; } ;
struct ice_pf {int num_alloc_vfs; TYPE_1__* pdev; struct ice_vf* vf; int /*<<< orphan*/  state; struct ice_hw hw; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  GL_MDET_RX ; 
 int GL_MDET_RX_MAL_TYPE_M ; 
 int GL_MDET_RX_MAL_TYPE_S ; 
 int GL_MDET_RX_PF_NUM_M ; 
 int GL_MDET_RX_PF_NUM_S ; 
 int GL_MDET_RX_QNUM_M ; 
 int GL_MDET_RX_QNUM_S ; 
 int GL_MDET_RX_VALID_M ; 
 int GL_MDET_RX_VF_NUM_M ; 
 int GL_MDET_RX_VF_NUM_S ; 
 int /*<<< orphan*/  GL_MDET_TX_PQM ; 
 int GL_MDET_TX_PQM_MAL_TYPE_M ; 
 int GL_MDET_TX_PQM_MAL_TYPE_S ; 
 int GL_MDET_TX_PQM_PF_NUM_M ; 
 int GL_MDET_TX_PQM_PF_NUM_S ; 
 int GL_MDET_TX_PQM_QNUM_M ; 
 int GL_MDET_TX_PQM_QNUM_S ; 
 int GL_MDET_TX_PQM_VALID_M ; 
 int GL_MDET_TX_PQM_VF_NUM_M ; 
 int GL_MDET_TX_PQM_VF_NUM_S ; 
 int /*<<< orphan*/  GL_MDET_TX_TCLAN ; 
 int GL_MDET_TX_TCLAN_MAL_TYPE_M ; 
 int GL_MDET_TX_TCLAN_MAL_TYPE_S ; 
 int GL_MDET_TX_TCLAN_PF_NUM_M ; 
 int GL_MDET_TX_TCLAN_PF_NUM_S ; 
 int GL_MDET_TX_TCLAN_QNUM_M ; 
 int GL_MDET_TX_TCLAN_QNUM_S ; 
 int GL_MDET_TX_TCLAN_VALID_M ; 
 int GL_MDET_TX_TCLAN_VF_NUM_M ; 
 int GL_MDET_TX_TCLAN_VF_NUM_S ; 
 scalar_t__ ICE_MDD_EVENTS_THRESHOLD ; 
 int /*<<< orphan*/  PF_MDET_RX ; 
 int PF_MDET_RX_VALID_M ; 
 int /*<<< orphan*/  PF_MDET_TX_PQM ; 
 int PF_MDET_TX_PQM_VALID_M ; 
 int /*<<< orphan*/  PF_MDET_TX_TCLAN ; 
 int PF_MDET_TX_TCLAN_VALID_M ; 
 int /*<<< orphan*/  VP_MDET_RX (int) ; 
 int VP_MDET_RX_VALID_M ; 
 int /*<<< orphan*/  VP_MDET_TX_PQM (int) ; 
 int VP_MDET_TX_PQM_VALID_M ; 
 int /*<<< orphan*/  VP_MDET_TX_TCLAN (int) ; 
 int VP_MDET_TX_TCLAN_VALID_M ; 
 int /*<<< orphan*/  VP_MDET_TX_TDPU (int) ; 
 int VP_MDET_TX_TDPU_VALID_M ; 
 int /*<<< orphan*/  __ICE_MDD_EVENT_PENDING ; 
 int /*<<< orphan*/  __ICE_NEEDS_RESTART ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  ice_service_task_schedule (struct ice_pf*) ; 
 scalar_t__ netif_msg_rx_err (struct ice_pf*) ; 
 scalar_t__ netif_msg_tx_err (struct ice_pf*) ; 
 int rd32 (struct ice_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wr32 (struct ice_hw*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void ice_handle_mdd_event(struct ice_pf *pf)
{
	struct ice_hw *hw = &pf->hw;
	bool mdd_detected = false;
	u32 reg;
	int i;

	if (!test_and_clear_bit(__ICE_MDD_EVENT_PENDING, pf->state))
		return;

	/* find what triggered the MDD event */
	reg = rd32(hw, GL_MDET_TX_PQM);
	if (reg & GL_MDET_TX_PQM_VALID_M) {
		u8 pf_num = (reg & GL_MDET_TX_PQM_PF_NUM_M) >>
				GL_MDET_TX_PQM_PF_NUM_S;
		u16 vf_num = (reg & GL_MDET_TX_PQM_VF_NUM_M) >>
				GL_MDET_TX_PQM_VF_NUM_S;
		u8 event = (reg & GL_MDET_TX_PQM_MAL_TYPE_M) >>
				GL_MDET_TX_PQM_MAL_TYPE_S;
		u16 queue = ((reg & GL_MDET_TX_PQM_QNUM_M) >>
				GL_MDET_TX_PQM_QNUM_S);

		if (netif_msg_tx_err(pf))
			dev_info(&pf->pdev->dev, "Malicious Driver Detection event %d on TX queue %d PF# %d VF# %d\n",
				 event, queue, pf_num, vf_num);
		wr32(hw, GL_MDET_TX_PQM, 0xffffffff);
		mdd_detected = true;
	}

	reg = rd32(hw, GL_MDET_TX_TCLAN);
	if (reg & GL_MDET_TX_TCLAN_VALID_M) {
		u8 pf_num = (reg & GL_MDET_TX_TCLAN_PF_NUM_M) >>
				GL_MDET_TX_TCLAN_PF_NUM_S;
		u16 vf_num = (reg & GL_MDET_TX_TCLAN_VF_NUM_M) >>
				GL_MDET_TX_TCLAN_VF_NUM_S;
		u8 event = (reg & GL_MDET_TX_TCLAN_MAL_TYPE_M) >>
				GL_MDET_TX_TCLAN_MAL_TYPE_S;
		u16 queue = ((reg & GL_MDET_TX_TCLAN_QNUM_M) >>
				GL_MDET_TX_TCLAN_QNUM_S);

		if (netif_msg_rx_err(pf))
			dev_info(&pf->pdev->dev, "Malicious Driver Detection event %d on TX queue %d PF# %d VF# %d\n",
				 event, queue, pf_num, vf_num);
		wr32(hw, GL_MDET_TX_TCLAN, 0xffffffff);
		mdd_detected = true;
	}

	reg = rd32(hw, GL_MDET_RX);
	if (reg & GL_MDET_RX_VALID_M) {
		u8 pf_num = (reg & GL_MDET_RX_PF_NUM_M) >>
				GL_MDET_RX_PF_NUM_S;
		u16 vf_num = (reg & GL_MDET_RX_VF_NUM_M) >>
				GL_MDET_RX_VF_NUM_S;
		u8 event = (reg & GL_MDET_RX_MAL_TYPE_M) >>
				GL_MDET_RX_MAL_TYPE_S;
		u16 queue = ((reg & GL_MDET_RX_QNUM_M) >>
				GL_MDET_RX_QNUM_S);

		if (netif_msg_rx_err(pf))
			dev_info(&pf->pdev->dev, "Malicious Driver Detection event %d on RX queue %d PF# %d VF# %d\n",
				 event, queue, pf_num, vf_num);
		wr32(hw, GL_MDET_RX, 0xffffffff);
		mdd_detected = true;
	}

	if (mdd_detected) {
		bool pf_mdd_detected = false;

		reg = rd32(hw, PF_MDET_TX_PQM);
		if (reg & PF_MDET_TX_PQM_VALID_M) {
			wr32(hw, PF_MDET_TX_PQM, 0xFFFF);
			dev_info(&pf->pdev->dev, "TX driver issue detected, PF reset issued\n");
			pf_mdd_detected = true;
		}

		reg = rd32(hw, PF_MDET_TX_TCLAN);
		if (reg & PF_MDET_TX_TCLAN_VALID_M) {
			wr32(hw, PF_MDET_TX_TCLAN, 0xFFFF);
			dev_info(&pf->pdev->dev, "TX driver issue detected, PF reset issued\n");
			pf_mdd_detected = true;
		}

		reg = rd32(hw, PF_MDET_RX);
		if (reg & PF_MDET_RX_VALID_M) {
			wr32(hw, PF_MDET_RX, 0xFFFF);
			dev_info(&pf->pdev->dev, "RX driver issue detected, PF reset issued\n");
			pf_mdd_detected = true;
		}
		/* Queue belongs to the PF initiate a reset */
		if (pf_mdd_detected) {
			set_bit(__ICE_NEEDS_RESTART, pf->state);
			ice_service_task_schedule(pf);
		}
	}

	/* check to see if one of the VFs caused the MDD */
	for (i = 0; i < pf->num_alloc_vfs; i++) {
		struct ice_vf *vf = &pf->vf[i];

		bool vf_mdd_detected = false;

		reg = rd32(hw, VP_MDET_TX_PQM(i));
		if (reg & VP_MDET_TX_PQM_VALID_M) {
			wr32(hw, VP_MDET_TX_PQM(i), 0xFFFF);
			vf_mdd_detected = true;
			dev_info(&pf->pdev->dev, "TX driver issue detected on VF %d\n",
				 i);
		}

		reg = rd32(hw, VP_MDET_TX_TCLAN(i));
		if (reg & VP_MDET_TX_TCLAN_VALID_M) {
			wr32(hw, VP_MDET_TX_TCLAN(i), 0xFFFF);
			vf_mdd_detected = true;
			dev_info(&pf->pdev->dev, "TX driver issue detected on VF %d\n",
				 i);
		}

		reg = rd32(hw, VP_MDET_TX_TDPU(i));
		if (reg & VP_MDET_TX_TDPU_VALID_M) {
			wr32(hw, VP_MDET_TX_TDPU(i), 0xFFFF);
			vf_mdd_detected = true;
			dev_info(&pf->pdev->dev, "TX driver issue detected on VF %d\n",
				 i);
		}

		reg = rd32(hw, VP_MDET_RX(i));
		if (reg & VP_MDET_RX_VALID_M) {
			wr32(hw, VP_MDET_RX(i), 0xFFFF);
			vf_mdd_detected = true;
			dev_info(&pf->pdev->dev, "RX driver issue detected on VF %d\n",
				 i);
		}

		if (vf_mdd_detected) {
			vf->num_mdd_events++;
			if (vf->num_mdd_events &&
			    vf->num_mdd_events <= ICE_MDD_EVENTS_THRESHOLD)
				dev_info(&pf->pdev->dev,
					 "VF %d has had %llu MDD events since last boot, Admin might need to reload AVF driver with this number of events\n",
					 i, vf->num_mdd_events);
		}
	}
}