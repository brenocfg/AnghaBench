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
struct bnx2_napi {int int_num; int last_status_idx; } ;
struct bnx2 {int irq_nvecs; int hc_cmd; struct bnx2_napi* bnx2_napi; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNX2_HC_COMMAND ; 
 int BNX2_HC_COMMAND_COAL_NOW ; 
 int /*<<< orphan*/  BNX2_PCICFG_INT_ACK_CMD ; 
 int BNX2_PCICFG_INT_ACK_CMD_INDEX_VALID ; 
 int BNX2_PCICFG_INT_ACK_CMD_MASK_INT ; 
 int /*<<< orphan*/  BNX2_WR (struct bnx2*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
bnx2_enable_int(struct bnx2 *bp)
{
	int i;
	struct bnx2_napi *bnapi;

	for (i = 0; i < bp->irq_nvecs; i++) {
		bnapi = &bp->bnx2_napi[i];

		BNX2_WR(bp, BNX2_PCICFG_INT_ACK_CMD, bnapi->int_num |
			BNX2_PCICFG_INT_ACK_CMD_INDEX_VALID |
			BNX2_PCICFG_INT_ACK_CMD_MASK_INT |
			bnapi->last_status_idx);

		BNX2_WR(bp, BNX2_PCICFG_INT_ACK_CMD, bnapi->int_num |
			BNX2_PCICFG_INT_ACK_CMD_INDEX_VALID |
			bnapi->last_status_idx);
	}
	BNX2_WR(bp, BNX2_HC_COMMAND, bp->hc_cmd | BNX2_HC_COMMAND_COAL_NOW);
}