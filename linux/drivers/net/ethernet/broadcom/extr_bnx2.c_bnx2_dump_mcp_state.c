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
typedef  int /*<<< orphan*/  u32 ;
struct net_device {int dummy; } ;
struct bnx2 {struct net_device* dev; } ;

/* Variables and functions */
 int BNX2_BC_RESET_TYPE ; 
 int BNX2_BC_STATE_CONDITION ; 
 int BNX2_BC_STATE_RESET_TYPE ; 
 scalar_t__ BNX2_CHIP (struct bnx2*) ; 
 scalar_t__ BNX2_CHIP_5709 ; 
 int BNX2_DEV_INFO_SIGNATURE ; 
 int BNX2_DRV_MB ; 
 int BNX2_DRV_PULSE_MB ; 
 int BNX2_FW_MB ; 
 int BNX2_LINK_STATUS ; 
 int /*<<< orphan*/  BNX2_MCP_CPU_EVENT_MASK ; 
 int /*<<< orphan*/  BNX2_MCP_CPU_INSTRUCTION ; 
 int /*<<< orphan*/  BNX2_MCP_CPU_MODE ; 
 int /*<<< orphan*/  BNX2_MCP_CPU_PROGRAM_COUNTER ; 
 int /*<<< orphan*/  BNX2_MCP_CPU_STATE ; 
 int /*<<< orphan*/  BNX2_MCP_STATE_P0 ; 
 int /*<<< orphan*/  BNX2_MCP_STATE_P0_5708 ; 
 int /*<<< orphan*/  BNX2_MCP_STATE_P1 ; 
 int /*<<< orphan*/  BNX2_MCP_STATE_P1_5708 ; 
 int /*<<< orphan*/  DP_SHMEM_LINE (struct bnx2*,int) ; 
 int /*<<< orphan*/  bnx2_reg_rd_ind (struct bnx2*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bnx2_shmem_rd (struct bnx2*,int) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*,...) ; 
 int /*<<< orphan*/  pr_cont (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bnx2_dump_mcp_state(struct bnx2 *bp)
{
	struct net_device *dev = bp->dev;
	u32 mcp_p0, mcp_p1;

	netdev_err(dev, "<--- start MCP states dump --->\n");
	if (BNX2_CHIP(bp) == BNX2_CHIP_5709) {
		mcp_p0 = BNX2_MCP_STATE_P0;
		mcp_p1 = BNX2_MCP_STATE_P1;
	} else {
		mcp_p0 = BNX2_MCP_STATE_P0_5708;
		mcp_p1 = BNX2_MCP_STATE_P1_5708;
	}
	netdev_err(dev, "DEBUG: MCP_STATE_P0[%08x] MCP_STATE_P1[%08x]\n",
		   bnx2_reg_rd_ind(bp, mcp_p0), bnx2_reg_rd_ind(bp, mcp_p1));
	netdev_err(dev, "DEBUG: MCP mode[%08x] state[%08x] evt_mask[%08x]\n",
		   bnx2_reg_rd_ind(bp, BNX2_MCP_CPU_MODE),
		   bnx2_reg_rd_ind(bp, BNX2_MCP_CPU_STATE),
		   bnx2_reg_rd_ind(bp, BNX2_MCP_CPU_EVENT_MASK));
	netdev_err(dev, "DEBUG: pc[%08x] pc[%08x] instr[%08x]\n",
		   bnx2_reg_rd_ind(bp, BNX2_MCP_CPU_PROGRAM_COUNTER),
		   bnx2_reg_rd_ind(bp, BNX2_MCP_CPU_PROGRAM_COUNTER),
		   bnx2_reg_rd_ind(bp, BNX2_MCP_CPU_INSTRUCTION));
	netdev_err(dev, "DEBUG: shmem states:\n");
	netdev_err(dev, "DEBUG: drv_mb[%08x] fw_mb[%08x] link_status[%08x]",
		   bnx2_shmem_rd(bp, BNX2_DRV_MB),
		   bnx2_shmem_rd(bp, BNX2_FW_MB),
		   bnx2_shmem_rd(bp, BNX2_LINK_STATUS));
	pr_cont(" drv_pulse_mb[%08x]\n", bnx2_shmem_rd(bp, BNX2_DRV_PULSE_MB));
	netdev_err(dev, "DEBUG: dev_info_signature[%08x] reset_type[%08x]",
		   bnx2_shmem_rd(bp, BNX2_DEV_INFO_SIGNATURE),
		   bnx2_shmem_rd(bp, BNX2_BC_STATE_RESET_TYPE));
	pr_cont(" condition[%08x]\n",
		bnx2_shmem_rd(bp, BNX2_BC_STATE_CONDITION));
	DP_SHMEM_LINE(bp, BNX2_BC_RESET_TYPE);
	DP_SHMEM_LINE(bp, 0x3cc);
	DP_SHMEM_LINE(bp, 0x3dc);
	DP_SHMEM_LINE(bp, 0x3ec);
	netdev_err(dev, "DEBUG: 0x3fc[%08x]\n", bnx2_shmem_rd(bp, 0x3fc));
	netdev_err(dev, "<--- end MCP states dump --->\n");
}