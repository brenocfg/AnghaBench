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
struct TYPE_3__ {scalar_t__ reset_stats; int /*<<< orphan*/  pport_num; } ;
struct TYPE_4__ {TYPE_1__ params; } ;
struct lancer_cmd_req_pport_stats {TYPE_2__ cmd_params; int /*<<< orphan*/  hdr; } ;
struct be_mcc_wrb {int dummy; } ;
struct be_dma_mem {int /*<<< orphan*/  size; struct lancer_cmd_req_pport_stats* va; } ;
struct be_adapter {int stats_cmd_sent; int /*<<< orphan*/  mcc_lock; int /*<<< orphan*/  hba_port_num; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_SUBSYSTEM_ETH ; 
 int EBUSY ; 
 int EPERM ; 
 int /*<<< orphan*/  OPCODE_ETH_GET_PPORT_STATS ; 
 int /*<<< orphan*/  be_cmd_allowed (struct be_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int be_mcc_notify (struct be_adapter*) ; 
 int /*<<< orphan*/  be_wrb_cmd_hdr_prepare (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct be_mcc_wrb*,struct be_dma_mem*) ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct be_mcc_wrb* wrb_from_mccq (struct be_adapter*) ; 

int lancer_cmd_get_pport_stats(struct be_adapter *adapter,
			       struct be_dma_mem *nonemb_cmd)
{
	struct be_mcc_wrb *wrb;
	struct lancer_cmd_req_pport_stats *req;
	int status = 0;

	if (!be_cmd_allowed(adapter, OPCODE_ETH_GET_PPORT_STATS,
			    CMD_SUBSYSTEM_ETH))
		return -EPERM;

	mutex_lock(&adapter->mcc_lock);

	wrb = wrb_from_mccq(adapter);
	if (!wrb) {
		status = -EBUSY;
		goto err;
	}
	req = nonemb_cmd->va;

	be_wrb_cmd_hdr_prepare(&req->hdr, CMD_SUBSYSTEM_ETH,
			       OPCODE_ETH_GET_PPORT_STATS, nonemb_cmd->size,
			       wrb, nonemb_cmd);

	req->cmd_params.params.pport_num = cpu_to_le16(adapter->hba_port_num);
	req->cmd_params.params.reset_stats = 0;

	status = be_mcc_notify(adapter);
	if (status)
		goto err;

	adapter->stats_cmd_sent = true;

err:
	mutex_unlock(&adapter->mcc_lock);
	return status;
}