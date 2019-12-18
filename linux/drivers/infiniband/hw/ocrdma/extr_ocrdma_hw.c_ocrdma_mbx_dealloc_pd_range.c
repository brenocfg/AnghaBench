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
struct ocrdma_mqe {int dummy; } ;
struct ocrdma_dev {TYPE_1__* pd_mgr; } ;
struct ocrdma_dealloc_pd_range {scalar_t__ pd_count; int /*<<< orphan*/  start_pd_id; } ;
struct TYPE_2__ {scalar_t__ max_dpp_pd; int /*<<< orphan*/  pd_dpp_start; scalar_t__ max_normal_pd; int /*<<< orphan*/  pd_norm_start; } ;

/* Variables and functions */
 int /*<<< orphan*/  OCRDMA_CMD_DEALLOC_PD_RANGE ; 
 int /*<<< orphan*/  kfree (struct ocrdma_dealloc_pd_range*) ; 
 struct ocrdma_dealloc_pd_range* ocrdma_init_emb_mqe (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ocrdma_mbx_cmd (struct ocrdma_dev*,struct ocrdma_mqe*) ; 

__attribute__((used)) static void ocrdma_mbx_dealloc_pd_range(struct ocrdma_dev *dev)
{
	struct ocrdma_dealloc_pd_range *cmd;

	/* return normal PDs to firmware */
	cmd = ocrdma_init_emb_mqe(OCRDMA_CMD_DEALLOC_PD_RANGE, sizeof(*cmd));
	if (!cmd)
		goto mbx_err;

	if (dev->pd_mgr->max_normal_pd) {
		cmd->start_pd_id = dev->pd_mgr->pd_norm_start;
		cmd->pd_count = dev->pd_mgr->max_normal_pd;
		ocrdma_mbx_cmd(dev, (struct ocrdma_mqe *)cmd);
	}

	if (dev->pd_mgr->max_dpp_pd) {
		kfree(cmd);
		/* return DPP PDs to firmware */
		cmd = ocrdma_init_emb_mqe(OCRDMA_CMD_DEALLOC_PD_RANGE,
					  sizeof(*cmd));
		if (!cmd)
			goto mbx_err;

		cmd->start_pd_id = dev->pd_mgr->pd_dpp_start;
		cmd->pd_count = dev->pd_mgr->max_dpp_pd;
		ocrdma_mbx_cmd(dev, (struct ocrdma_mqe *)cmd);
	}
mbx_err:
	kfree(cmd);
}