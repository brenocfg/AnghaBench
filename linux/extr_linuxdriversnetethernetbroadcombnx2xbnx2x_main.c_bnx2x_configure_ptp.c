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
typedef  scalar_t__ u32 ;
struct bnx2x {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNX2X_ERR (char*) ; 
 int BP_PORT (struct bnx2x*) ; 
 int EFAULT ; 
 int /*<<< orphan*/  NIG_REG_P0_LLH_PTP_HOST_BUF_SEQID ; 
 int /*<<< orphan*/  NIG_REG_P0_LLH_PTP_PARAM_MASK ; 
 int /*<<< orphan*/  NIG_REG_P0_LLH_PTP_RULE_MASK ; 
 int /*<<< orphan*/  NIG_REG_P0_LLH_PTP_TO_HOST ; 
 int /*<<< orphan*/  NIG_REG_P0_PTP_EN ; 
 int /*<<< orphan*/  NIG_REG_P0_TLLH_PTP_BUF_SEQID ; 
 int /*<<< orphan*/  NIG_REG_P0_TLLH_PTP_PARAM_MASK ; 
 int /*<<< orphan*/  NIG_REG_P0_TLLH_PTP_RULE_MASK ; 
 int /*<<< orphan*/  NIG_REG_P1_LLH_PTP_HOST_BUF_SEQID ; 
 int /*<<< orphan*/  NIG_REG_P1_LLH_PTP_PARAM_MASK ; 
 int /*<<< orphan*/  NIG_REG_P1_LLH_PTP_RULE_MASK ; 
 int /*<<< orphan*/  NIG_REG_P1_LLH_PTP_TO_HOST ; 
 int /*<<< orphan*/  NIG_REG_P1_PTP_EN ; 
 int /*<<< orphan*/  NIG_REG_P1_TLLH_PTP_BUF_SEQID ; 
 int /*<<< orphan*/  NIG_REG_P1_TLLH_PTP_PARAM_MASK ; 
 int /*<<< orphan*/  NIG_REG_P1_TLLH_PTP_RULE_MASK ; 
 scalar_t__ NIG_REG_TIMESYNC_GEN_REG ; 
 int /*<<< orphan*/  REG_WR (struct bnx2x*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  REG_WR_DMAE (struct bnx2x*,scalar_t__,scalar_t__*,int) ; 
 int bnx2x_send_reset_timesync_ramrod (struct bnx2x*) ; 
 scalar_t__ tsgen_ctrl ; 

__attribute__((used)) static int bnx2x_configure_ptp(struct bnx2x *bp)
{
	int rc, port = BP_PORT(bp);
	u32 wb_data[2];

	/* Reset PTP event detection rules - will be configured in the IOCTL */
	REG_WR(bp, port ? NIG_REG_P1_LLH_PTP_PARAM_MASK :
	       NIG_REG_P0_LLH_PTP_PARAM_MASK, 0x7FF);
	REG_WR(bp, port ? NIG_REG_P1_LLH_PTP_RULE_MASK :
	       NIG_REG_P0_LLH_PTP_RULE_MASK, 0x3FFF);
	REG_WR(bp, port ? NIG_REG_P1_TLLH_PTP_PARAM_MASK :
	       NIG_REG_P0_TLLH_PTP_PARAM_MASK, 0x7FF);
	REG_WR(bp, port ? NIG_REG_P1_TLLH_PTP_RULE_MASK :
	       NIG_REG_P0_TLLH_PTP_RULE_MASK, 0x3FFF);

	/* Disable PTP packets to host - will be configured in the IOCTL*/
	REG_WR(bp, port ? NIG_REG_P1_LLH_PTP_TO_HOST :
	       NIG_REG_P0_LLH_PTP_TO_HOST, 0x0);

	/* Enable the PTP feature */
	REG_WR(bp, port ? NIG_REG_P1_PTP_EN :
	       NIG_REG_P0_PTP_EN, 0x3F);

	/* Enable the free-running counter */
	wb_data[0] = 0;
	wb_data[1] = 0;
	REG_WR_DMAE(bp, NIG_REG_TIMESYNC_GEN_REG + tsgen_ctrl, wb_data, 2);

	/* Reset drift register (offset register is not reset) */
	rc = bnx2x_send_reset_timesync_ramrod(bp);
	if (rc) {
		BNX2X_ERR("Failed to reset PHC drift register\n");
		return -EFAULT;
	}

	/* Reset possibly old timestamps */
	REG_WR(bp, port ? NIG_REG_P1_LLH_PTP_HOST_BUF_SEQID :
	       NIG_REG_P0_LLH_PTP_HOST_BUF_SEQID, 0x10000);
	REG_WR(bp, port ? NIG_REG_P1_TLLH_PTP_BUF_SEQID :
	       NIG_REG_P0_TLLH_PTP_BUF_SEQID, 0x10000);

	return 0;
}