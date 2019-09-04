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
struct bnx2x {int* mf_config; int /*<<< orphan*/  flags; } ;
struct TYPE_2__ {int /*<<< orphan*/  config; } ;

/* Variables and functions */
 int BP_MAX_VN_NUM (struct bnx2x*) ; 
 scalar_t__ BP_NOMCP (struct bnx2x*) ; 
 int BP_PATH (struct bnx2x*) ; 
 int BP_PORT (struct bnx2x*) ; 
 size_t BP_VN (struct bnx2x*) ; 
 scalar_t__ CHIP_MODE_IS_4_PORT (struct bnx2x*) ; 
 int /*<<< orphan*/  DP (int /*<<< orphan*/ ,char*) ; 
 int E1H_FUNC_MAX ; 
 int FUNC_MF_CFG_FUNC_DISABLED ; 
 int MF_CFG_RD (struct bnx2x*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MF_FUNC_DIS ; 
 int /*<<< orphan*/  NETIF_MSG_IFUP ; 
 int VN_0 ; 
 TYPE_1__* func_mf_config ; 

void bnx2x_read_mf_cfg(struct bnx2x *bp)
{
	int vn, n = (CHIP_MODE_IS_4_PORT(bp) ? 2 : 1);

	if (BP_NOMCP(bp))
		return; /* what should be the default value in this case */

	/* For 2 port configuration the absolute function number formula
	 * is:
	 *      abs_func = 2 * vn + BP_PORT + BP_PATH
	 *
	 *      and there are 4 functions per port
	 *
	 * For 4 port configuration it is
	 *      abs_func = 4 * vn + 2 * BP_PORT + BP_PATH
	 *
	 *      and there are 2 functions per port
	 */
	for (vn = VN_0; vn < BP_MAX_VN_NUM(bp); vn++) {
		int /*abs*/func = n * (2 * vn + BP_PORT(bp)) + BP_PATH(bp);

		if (func >= E1H_FUNC_MAX)
			break;

		bp->mf_config[vn] =
			MF_CFG_RD(bp, func_mf_config[func].config);
	}
	if (bp->mf_config[BP_VN(bp)] & FUNC_MF_CFG_FUNC_DISABLED) {
		DP(NETIF_MSG_IFUP, "mf_cfg function disabled\n");
		bp->flags |= MF_FUNC_DIS;
	} else {
		DP(NETIF_MSG_IFUP, "mf_cfg function enabled\n");
		bp->flags &= ~MF_FUNC_DIS;
	}
}