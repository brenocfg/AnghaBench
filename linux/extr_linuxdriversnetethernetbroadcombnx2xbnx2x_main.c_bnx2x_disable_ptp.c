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
struct bnx2x {int dummy; } ;

/* Variables and functions */
 int BP_PORT (struct bnx2x*) ; 
 int /*<<< orphan*/  NIG_REG_P0_LLH_PTP_PARAM_MASK ; 
 int /*<<< orphan*/  NIG_REG_P0_LLH_PTP_RULE_MASK ; 
 int /*<<< orphan*/  NIG_REG_P0_LLH_PTP_TO_HOST ; 
 int /*<<< orphan*/  NIG_REG_P0_PTP_EN ; 
 int /*<<< orphan*/  NIG_REG_P0_TLLH_PTP_PARAM_MASK ; 
 int /*<<< orphan*/  NIG_REG_P0_TLLH_PTP_RULE_MASK ; 
 int /*<<< orphan*/  NIG_REG_P1_LLH_PTP_PARAM_MASK ; 
 int /*<<< orphan*/  NIG_REG_P1_LLH_PTP_RULE_MASK ; 
 int /*<<< orphan*/  NIG_REG_P1_LLH_PTP_TO_HOST ; 
 int /*<<< orphan*/  NIG_REG_P1_PTP_EN ; 
 int /*<<< orphan*/  NIG_REG_P1_TLLH_PTP_PARAM_MASK ; 
 int /*<<< orphan*/  NIG_REG_P1_TLLH_PTP_RULE_MASK ; 
 int /*<<< orphan*/  REG_WR (struct bnx2x*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void bnx2x_disable_ptp(struct bnx2x *bp)
{
	int port = BP_PORT(bp);

	/* Disable sending PTP packets to host */
	REG_WR(bp, port ? NIG_REG_P1_LLH_PTP_TO_HOST :
	       NIG_REG_P0_LLH_PTP_TO_HOST, 0x0);

	/* Reset PTP event detection rules */
	REG_WR(bp, port ? NIG_REG_P1_LLH_PTP_PARAM_MASK :
	       NIG_REG_P0_LLH_PTP_PARAM_MASK, 0x7FF);
	REG_WR(bp, port ? NIG_REG_P1_LLH_PTP_RULE_MASK :
	       NIG_REG_P0_LLH_PTP_RULE_MASK, 0x3FFF);
	REG_WR(bp, port ? NIG_REG_P1_TLLH_PTP_PARAM_MASK :
	       NIG_REG_P0_TLLH_PTP_PARAM_MASK, 0x7FF);
	REG_WR(bp, port ? NIG_REG_P1_TLLH_PTP_RULE_MASK :
	       NIG_REG_P0_TLLH_PTP_RULE_MASK, 0x3FFF);

	/* Disable the PTP feature */
	REG_WR(bp, port ? NIG_REG_P1_PTP_EN :
	       NIG_REG_P0_PTP_EN, 0x0);
}