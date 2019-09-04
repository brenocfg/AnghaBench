#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct be_mcc_wrb {int dummy; } ;
struct be_dma_mem {int /*<<< orphan*/  size; struct be_cmd_req_hdr* va; } ;
struct be_cmd_req_hdr {int version; } ;
struct be_adapter {int stats_cmd_sent; int /*<<< orphan*/  mcc_lock; } ;

/* Variables and functions */
 scalar_t__ BE2_chip (struct be_adapter*) ; 
 scalar_t__ BE3_chip (struct be_adapter*) ; 
 int /*<<< orphan*/  CMD_SUBSYSTEM_ETH ; 
 int EBUSY ; 
 int /*<<< orphan*/  OPCODE_ETH_GET_STATISTICS ; 
 int be_mcc_notify (struct be_adapter*) ; 
 int /*<<< orphan*/  be_wrb_cmd_hdr_prepare (struct be_cmd_req_hdr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct be_mcc_wrb*,struct be_dma_mem*) ; 
 scalar_t__ lancer_chip (struct be_adapter*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct be_mcc_wrb* wrb_from_mccq (struct be_adapter*) ; 

int be_cmd_get_stats(struct be_adapter *adapter, struct be_dma_mem *nonemb_cmd)
{
	struct be_mcc_wrb *wrb;
	struct be_cmd_req_hdr *hdr;
	int status = 0;

	mutex_lock(&adapter->mcc_lock);

	wrb = wrb_from_mccq(adapter);
	if (!wrb) {
		status = -EBUSY;
		goto err;
	}
	hdr = nonemb_cmd->va;

	be_wrb_cmd_hdr_prepare(hdr, CMD_SUBSYSTEM_ETH,
			       OPCODE_ETH_GET_STATISTICS, nonemb_cmd->size, wrb,
			       nonemb_cmd);

	/* version 1 of the cmd is not supported only by BE2 */
	if (BE2_chip(adapter))
		hdr->version = 0;
	if (BE3_chip(adapter) || lancer_chip(adapter))
		hdr->version = 1;
	else
		hdr->version = 2;

	status = be_mcc_notify(adapter);
	if (status)
		goto err;

	adapter->stats_cmd_sent = true;

err:
	mutex_unlock(&adapter->mcc_lock);
	return status;
}