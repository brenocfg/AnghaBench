#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_5__ {int /*<<< orphan*/  shmem2_base; int /*<<< orphan*/  shmem_base; } ;
struct bnx2x {TYPE_2__ common; } ;
struct TYPE_4__ {int /*<<< orphan*/  config2; } ;
struct TYPE_6__ {TYPE_1__ shared_hw_config; } ;

/* Variables and functions */
 scalar_t__ BP_NOMCP (struct bnx2x*) ; 
 int /*<<< orphan*/  DP (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  MISC_REG_SPIO_EVENT_EN ; 
 int /*<<< orphan*/  MISC_REG_SPIO_INT ; 
 int /*<<< orphan*/  MISC_SPIO_INPUT_HI_Z ; 
 int MISC_SPIO_INT_OLD_SET_POS ; 
 int MISC_SPIO_SPIO5 ; 
 int /*<<< orphan*/  NETIF_MSG_HW ; 
 int PORT_0 ; 
 int PORT_MAX ; 
 int REG_RD (struct bnx2x*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_WR (struct bnx2x*,int /*<<< orphan*/ ,int) ; 
 int SHARED_HW_CFG_FAN_FAILURE_ENABLED ; 
 int SHARED_HW_CFG_FAN_FAILURE_MASK ; 
 int SHARED_HW_CFG_FAN_FAILURE_PHY_TYPE ; 
 int SHMEM_RD (struct bnx2x*,int /*<<< orphan*/ ) ; 
 int bnx2x_fan_failure_det_req (struct bnx2x*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bnx2x_set_spio (struct bnx2x*,int,int /*<<< orphan*/ ) ; 
 TYPE_3__ dev_info ; 

__attribute__((used)) static void bnx2x_setup_fan_failure_detection(struct bnx2x *bp)
{
	int is_required;
	u32 val;
	int port;

	if (BP_NOMCP(bp))
		return;

	is_required = 0;
	val = SHMEM_RD(bp, dev_info.shared_hw_config.config2) &
	      SHARED_HW_CFG_FAN_FAILURE_MASK;

	if (val == SHARED_HW_CFG_FAN_FAILURE_ENABLED)
		is_required = 1;

	/*
	 * The fan failure mechanism is usually related to the PHY type since
	 * the power consumption of the board is affected by the PHY. Currently,
	 * fan is required for most designs with SFX7101, BCM8727 and BCM8481.
	 */
	else if (val == SHARED_HW_CFG_FAN_FAILURE_PHY_TYPE)
		for (port = PORT_0; port < PORT_MAX; port++) {
			is_required |=
				bnx2x_fan_failure_det_req(
					bp,
					bp->common.shmem_base,
					bp->common.shmem2_base,
					port);
		}

	DP(NETIF_MSG_HW, "fan detection setting: %d\n", is_required);

	if (is_required == 0)
		return;

	/* Fan failure is indicated by SPIO 5 */
	bnx2x_set_spio(bp, MISC_SPIO_SPIO5, MISC_SPIO_INPUT_HI_Z);

	/* set to active low mode */
	val = REG_RD(bp, MISC_REG_SPIO_INT);
	val |= (MISC_SPIO_SPIO5 << MISC_SPIO_INT_OLD_SET_POS);
	REG_WR(bp, MISC_REG_SPIO_INT, val);

	/* enable interrupt to signal the IGU */
	val = REG_RD(bp, MISC_REG_SPIO_EVENT_EN);
	val |= MISC_SPIO_SPIO5;
	REG_WR(bp, MISC_REG_SPIO_EVENT_EN, val);
}