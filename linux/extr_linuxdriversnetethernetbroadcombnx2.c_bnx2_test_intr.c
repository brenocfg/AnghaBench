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
typedef  int u16 ;
struct bnx2 {int hc_cmd; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNX2_HC_COMMAND ; 
 int BNX2_HC_COMMAND_COAL_NOW ; 
 int /*<<< orphan*/  BNX2_PCICFG_INT_ACK_CMD ; 
 int BNX2_RD (struct bnx2*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BNX2_WR (struct bnx2*,int /*<<< orphan*/ ,int) ; 
 int ENODEV ; 
 int /*<<< orphan*/  msleep_interruptible (int) ; 
 int /*<<< orphan*/  netif_running (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
bnx2_test_intr(struct bnx2 *bp)
{
	int i;
	u16 status_idx;

	if (!netif_running(bp->dev))
		return -ENODEV;

	status_idx = BNX2_RD(bp, BNX2_PCICFG_INT_ACK_CMD) & 0xffff;

	/* This register is not touched during run-time. */
	BNX2_WR(bp, BNX2_HC_COMMAND, bp->hc_cmd | BNX2_HC_COMMAND_COAL_NOW);
	BNX2_RD(bp, BNX2_HC_COMMAND);

	for (i = 0; i < 10; i++) {
		if ((BNX2_RD(bp, BNX2_PCICFG_INT_ACK_CMD) & 0xffff) !=
			status_idx) {

			break;
		}

		msleep_interruptible(10);
	}
	if (i < 10)
		return 0;

	return -ENODEV;
}