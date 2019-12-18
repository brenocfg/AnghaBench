#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
typedef  int u16 ;
struct TYPE_8__ {int /*<<< orphan*/  opcode; } ;
struct ice_rq_event_info {int /*<<< orphan*/  msg_buf; TYPE_4__ desc; int /*<<< orphan*/  buf_len; } ;
struct TYPE_6__ {int /*<<< orphan*/  len; } ;
struct TYPE_5__ {int /*<<< orphan*/  len; } ;
struct ice_ctl_q_info {int /*<<< orphan*/  rq_buf_size; TYPE_2__ sq; TYPE_1__ rq; } ;
struct ice_hw {struct ice_ctl_q_info mailboxq; struct ice_ctl_q_info adminq; } ;
struct ice_pf {TYPE_3__* pdev; int /*<<< orphan*/  state; struct ice_hw hw; } ;
typedef  enum ice_status { ____Placeholder_ice_status } ice_status ;
typedef  enum ice_ctl_q { ____Placeholder_ice_ctl_q } ice_ctl_q ;
struct TYPE_7__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
#define  ICE_CTL_Q_ADMIN 133 
#define  ICE_CTL_Q_MAILBOX 132 
 scalar_t__ ICE_DFLT_IRQ_WORK ; 
 int ICE_ERR_AQ_NO_WORK ; 
 int PF_FW_ARQLEN_ARQCRIT_M ; 
 int PF_FW_ARQLEN_ARQOVFL_M ; 
 int PF_FW_ARQLEN_ARQVFE_M ; 
 int PF_FW_ATQLEN_ATQCRIT_M ; 
 int PF_FW_ATQLEN_ATQOVFL_M ; 
 int PF_FW_ATQLEN_ATQVFE_M ; 
 int /*<<< orphan*/  __ICE_RESET_FAILED ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,char const*,...) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  devm_kfree (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_kzalloc (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
#define  ice_aqc_opc_fw_logging 131 
#define  ice_aqc_opc_get_link_status 130 
#define  ice_aqc_opc_lldp_set_mib_change 129 
 int ice_clean_rq_elem (struct ice_hw*,struct ice_ctl_q_info*,struct ice_rq_event_info*,int*) ; 
 int /*<<< orphan*/  ice_dcb_process_lldp_set_mib_change (struct ice_pf*,struct ice_rq_event_info*) ; 
 int /*<<< orphan*/  ice_handle_link_event (struct ice_pf*,struct ice_rq_event_info*) ; 
#define  ice_mbx_opc_send_msg_to_pf 128 
 int /*<<< orphan*/  ice_output_fw_log (struct ice_hw*,TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ice_vc_process_vf_msg (struct ice_pf*,struct ice_rq_event_info*) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int rd32 (struct ice_hw*,int /*<<< orphan*/ ) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wr32 (struct ice_hw*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int __ice_clean_ctrlq(struct ice_pf *pf, enum ice_ctl_q q_type)
{
	struct ice_rq_event_info event;
	struct ice_hw *hw = &pf->hw;
	struct ice_ctl_q_info *cq;
	u16 pending, i = 0;
	const char *qtype;
	u32 oldval, val;

	/* Do not clean control queue if/when PF reset fails */
	if (test_bit(__ICE_RESET_FAILED, pf->state))
		return 0;

	switch (q_type) {
	case ICE_CTL_Q_ADMIN:
		cq = &hw->adminq;
		qtype = "Admin";
		break;
	case ICE_CTL_Q_MAILBOX:
		cq = &hw->mailboxq;
		qtype = "Mailbox";
		break;
	default:
		dev_warn(&pf->pdev->dev, "Unknown control queue type 0x%x\n",
			 q_type);
		return 0;
	}

	/* check for error indications - PF_xx_AxQLEN register layout for
	 * FW/MBX/SB are identical so just use defines for PF_FW_AxQLEN.
	 */
	val = rd32(hw, cq->rq.len);
	if (val & (PF_FW_ARQLEN_ARQVFE_M | PF_FW_ARQLEN_ARQOVFL_M |
		   PF_FW_ARQLEN_ARQCRIT_M)) {
		oldval = val;
		if (val & PF_FW_ARQLEN_ARQVFE_M)
			dev_dbg(&pf->pdev->dev,
				"%s Receive Queue VF Error detected\n", qtype);
		if (val & PF_FW_ARQLEN_ARQOVFL_M) {
			dev_dbg(&pf->pdev->dev,
				"%s Receive Queue Overflow Error detected\n",
				qtype);
		}
		if (val & PF_FW_ARQLEN_ARQCRIT_M)
			dev_dbg(&pf->pdev->dev,
				"%s Receive Queue Critical Error detected\n",
				qtype);
		val &= ~(PF_FW_ARQLEN_ARQVFE_M | PF_FW_ARQLEN_ARQOVFL_M |
			 PF_FW_ARQLEN_ARQCRIT_M);
		if (oldval != val)
			wr32(hw, cq->rq.len, val);
	}

	val = rd32(hw, cq->sq.len);
	if (val & (PF_FW_ATQLEN_ATQVFE_M | PF_FW_ATQLEN_ATQOVFL_M |
		   PF_FW_ATQLEN_ATQCRIT_M)) {
		oldval = val;
		if (val & PF_FW_ATQLEN_ATQVFE_M)
			dev_dbg(&pf->pdev->dev,
				"%s Send Queue VF Error detected\n", qtype);
		if (val & PF_FW_ATQLEN_ATQOVFL_M) {
			dev_dbg(&pf->pdev->dev,
				"%s Send Queue Overflow Error detected\n",
				qtype);
		}
		if (val & PF_FW_ATQLEN_ATQCRIT_M)
			dev_dbg(&pf->pdev->dev,
				"%s Send Queue Critical Error detected\n",
				qtype);
		val &= ~(PF_FW_ATQLEN_ATQVFE_M | PF_FW_ATQLEN_ATQOVFL_M |
			 PF_FW_ATQLEN_ATQCRIT_M);
		if (oldval != val)
			wr32(hw, cq->sq.len, val);
	}

	event.buf_len = cq->rq_buf_size;
	event.msg_buf = devm_kzalloc(&pf->pdev->dev, event.buf_len,
				     GFP_KERNEL);
	if (!event.msg_buf)
		return 0;

	do {
		enum ice_status ret;
		u16 opcode;

		ret = ice_clean_rq_elem(hw, cq, &event, &pending);
		if (ret == ICE_ERR_AQ_NO_WORK)
			break;
		if (ret) {
			dev_err(&pf->pdev->dev,
				"%s Receive Queue event error %d\n", qtype,
				ret);
			break;
		}

		opcode = le16_to_cpu(event.desc.opcode);

		switch (opcode) {
		case ice_aqc_opc_get_link_status:
			if (ice_handle_link_event(pf, &event))
				dev_err(&pf->pdev->dev,
					"Could not handle link event\n");
			break;
		case ice_mbx_opc_send_msg_to_pf:
			ice_vc_process_vf_msg(pf, &event);
			break;
		case ice_aqc_opc_fw_logging:
			ice_output_fw_log(hw, &event.desc, event.msg_buf);
			break;
		case ice_aqc_opc_lldp_set_mib_change:
			ice_dcb_process_lldp_set_mib_change(pf, &event);
			break;
		default:
			dev_dbg(&pf->pdev->dev,
				"%s Receive Queue unknown event 0x%04x ignored\n",
				qtype, opcode);
			break;
		}
	} while (pending && (i++ < ICE_DFLT_IRQ_WORK));

	devm_kfree(&pf->pdev->dev, event.msg_buf);

	return pending && (i == ICE_DFLT_IRQ_WORK);
}