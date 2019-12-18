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
struct efa_com_admin_queue {int dummy; } ;
struct efa_com_dev {int /*<<< orphan*/  efa_dev; struct efa_com_admin_queue aq; } ;
struct efa_com_create_cq_result {int /*<<< orphan*/  actual_depth; int /*<<< orphan*/  cq_idx; } ;
struct efa_com_create_cq_params {int entry_size_in_bytes; int /*<<< orphan*/  cq_depth; int /*<<< orphan*/  dma_addr; int /*<<< orphan*/  uarn; int /*<<< orphan*/  num_sub_cqs; } ;
struct efa_admin_create_cq_resp {int /*<<< orphan*/  cq_idx; } ;
struct TYPE_4__ {int /*<<< orphan*/  mem_addr_low; int /*<<< orphan*/  mem_addr_high; } ;
struct TYPE_3__ {int /*<<< orphan*/  opcode; } ;
struct efa_admin_create_cq_cmd {int cq_caps_2; TYPE_2__ cq_ba; int /*<<< orphan*/  uar; int /*<<< orphan*/  num_sub_cqs; int /*<<< orphan*/  cq_depth; TYPE_1__ aq_common_desc; } ;
struct efa_admin_aq_entry {int dummy; } ;
struct efa_admin_acq_entry {int dummy; } ;
typedef  int /*<<< orphan*/  create_cmd ;
typedef  int /*<<< orphan*/  cmd_completion ;

/* Variables and functions */
 int /*<<< orphan*/  EFA_ADMIN_CREATE_CQ ; 
 int EFA_ADMIN_CREATE_CQ_CMD_CQ_ENTRY_SIZE_WORDS_MASK ; 
 int efa_com_cmd_exec (struct efa_com_admin_queue*,struct efa_admin_aq_entry*,int,struct efa_admin_acq_entry*,int) ; 
 int /*<<< orphan*/  efa_com_set_dma_addr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ibdev_err_ratelimited (int /*<<< orphan*/ ,char*,int) ; 

int efa_com_create_cq(struct efa_com_dev *edev,
		      struct efa_com_create_cq_params *params,
		      struct efa_com_create_cq_result *result)
{
	struct efa_admin_create_cq_resp cmd_completion;
	struct efa_admin_create_cq_cmd create_cmd = {};
	struct efa_com_admin_queue *aq = &edev->aq;
	int err;

	create_cmd.aq_common_desc.opcode = EFA_ADMIN_CREATE_CQ;
	create_cmd.cq_caps_2 = (params->entry_size_in_bytes / 4) &
				EFA_ADMIN_CREATE_CQ_CMD_CQ_ENTRY_SIZE_WORDS_MASK;
	create_cmd.cq_depth = params->cq_depth;
	create_cmd.num_sub_cqs = params->num_sub_cqs;
	create_cmd.uar = params->uarn;

	efa_com_set_dma_addr(params->dma_addr,
			     &create_cmd.cq_ba.mem_addr_high,
			     &create_cmd.cq_ba.mem_addr_low);

	err = efa_com_cmd_exec(aq,
			       (struct efa_admin_aq_entry *)&create_cmd,
			       sizeof(create_cmd),
			       (struct efa_admin_acq_entry *)&cmd_completion,
			       sizeof(cmd_completion));
	if (err) {
		ibdev_err_ratelimited(edev->efa_dev,
				      "Failed to create cq[%d]\n", err);
		return err;
	}

	result->cq_idx = cmd_completion.cq_idx;
	result->actual_depth = params->cq_depth;

	return 0;
}