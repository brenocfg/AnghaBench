#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct efa_com_reg_mr_result {int /*<<< orphan*/  r_key; int /*<<< orphan*/  l_key; } ;
struct TYPE_11__ {int /*<<< orphan*/  mem_addr_high; int /*<<< orphan*/  mem_addr_low; } ;
struct TYPE_12__ {TYPE_4__ address; int /*<<< orphan*/  length; } ;
struct TYPE_13__ {TYPE_5__ pbl; int /*<<< orphan*/  inline_pbl_array; } ;
struct efa_com_reg_mr_params {int page_shift; int permissions; scalar_t__ indirect; TYPE_6__ pbl; scalar_t__ inline_pbl; int /*<<< orphan*/  iova; int /*<<< orphan*/  mr_length_in_bytes; int /*<<< orphan*/  pd; } ;
struct efa_com_admin_queue {int dummy; } ;
struct efa_com_dev {int /*<<< orphan*/  efa_dev; struct efa_com_admin_queue aq; } ;
struct efa_admin_reg_mr_resp {int /*<<< orphan*/  r_key; int /*<<< orphan*/  l_key; } ;
struct TYPE_14__ {int /*<<< orphan*/  flags; int /*<<< orphan*/  opcode; } ;
struct TYPE_8__ {int /*<<< orphan*/  mem_addr_high; int /*<<< orphan*/  mem_addr_low; } ;
struct TYPE_9__ {TYPE_1__ address; int /*<<< orphan*/  length; } ;
struct TYPE_10__ {TYPE_2__ pbl; int /*<<< orphan*/  inline_pbl_array; } ;
struct efa_admin_reg_mr_cmd {int flags; int permissions; TYPE_7__ aq_common_desc; TYPE_3__ pbl; int /*<<< orphan*/  iova; int /*<<< orphan*/  mr_length; int /*<<< orphan*/  pd; } ;
struct efa_admin_aq_entry {int dummy; } ;
struct efa_admin_acq_entry {int dummy; } ;
typedef  int /*<<< orphan*/  mr_cmd ;
typedef  int /*<<< orphan*/  cmd_completion ;

/* Variables and functions */
 int /*<<< orphan*/  EFA_ADMIN_AQ_COMMON_DESC_CTRL_DATA_INDIRECT_MASK ; 
 int /*<<< orphan*/  EFA_ADMIN_AQ_COMMON_DESC_CTRL_DATA_MASK ; 
 int /*<<< orphan*/  EFA_ADMIN_REG_MR ; 
 int EFA_ADMIN_REG_MR_CMD_LOCAL_WRITE_ENABLE_MASK ; 
 int EFA_ADMIN_REG_MR_CMD_PHYS_PAGE_SIZE_SHIFT_MASK ; 
 int efa_com_cmd_exec (struct efa_com_admin_queue*,struct efa_admin_aq_entry*,int,struct efa_admin_acq_entry*,int) ; 
 int /*<<< orphan*/  ibdev_err_ratelimited (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int efa_com_register_mr(struct efa_com_dev *edev,
			struct efa_com_reg_mr_params *params,
			struct efa_com_reg_mr_result *result)
{
	struct efa_admin_reg_mr_resp cmd_completion;
	struct efa_com_admin_queue *aq = &edev->aq;
	struct efa_admin_reg_mr_cmd mr_cmd = {};
	int err;

	mr_cmd.aq_common_desc.opcode = EFA_ADMIN_REG_MR;
	mr_cmd.pd = params->pd;
	mr_cmd.mr_length = params->mr_length_in_bytes;
	mr_cmd.flags |= params->page_shift &
		EFA_ADMIN_REG_MR_CMD_PHYS_PAGE_SIZE_SHIFT_MASK;
	mr_cmd.iova = params->iova;
	mr_cmd.permissions |= params->permissions &
			      EFA_ADMIN_REG_MR_CMD_LOCAL_WRITE_ENABLE_MASK;

	if (params->inline_pbl) {
		memcpy(mr_cmd.pbl.inline_pbl_array,
		       params->pbl.inline_pbl_array,
		       sizeof(mr_cmd.pbl.inline_pbl_array));
	} else {
		mr_cmd.pbl.pbl.length = params->pbl.pbl.length;
		mr_cmd.pbl.pbl.address.mem_addr_low =
			params->pbl.pbl.address.mem_addr_low;
		mr_cmd.pbl.pbl.address.mem_addr_high =
			params->pbl.pbl.address.mem_addr_high;
		mr_cmd.aq_common_desc.flags |=
			EFA_ADMIN_AQ_COMMON_DESC_CTRL_DATA_MASK;
		if (params->indirect)
			mr_cmd.aq_common_desc.flags |=
				EFA_ADMIN_AQ_COMMON_DESC_CTRL_DATA_INDIRECT_MASK;
	}

	err = efa_com_cmd_exec(aq,
			       (struct efa_admin_aq_entry *)&mr_cmd,
			       sizeof(mr_cmd),
			       (struct efa_admin_acq_entry *)&cmd_completion,
			       sizeof(cmd_completion));
	if (err) {
		ibdev_err_ratelimited(edev->efa_dev,
				      "Failed to register mr [%d]\n", err);
		return err;
	}

	result->l_key = cmd_completion.l_key;
	result->r_key = cmd_completion.r_key;

	return 0;
}