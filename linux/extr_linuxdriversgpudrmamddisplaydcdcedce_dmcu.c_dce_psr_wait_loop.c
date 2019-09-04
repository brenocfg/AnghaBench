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
struct TYPE_2__ {unsigned int wait_loop; } ;
union dce_dmcu_psr_config_data_wait_loop_reg1 {scalar_t__ u32; TYPE_1__ bits; } ;
struct dmcu {unsigned int cached_wait_loop_number; int /*<<< orphan*/  ctx; } ;
struct dce_dmcu {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MASTER_COMM_CMD_REG ; 
 int /*<<< orphan*/  MASTER_COMM_CMD_REG_BYTE0 ; 
 int /*<<< orphan*/  MASTER_COMM_CNTL_REG ; 
 int /*<<< orphan*/  MASTER_COMM_DATA_REG1 ; 
 int /*<<< orphan*/  MASTER_COMM_INTERRUPT ; 
 int PSR_SET_WAITLOOP ; 
 int /*<<< orphan*/  REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_UPDATE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  REG_WAIT (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 struct dce_dmcu* TO_DCE_DMCU (struct dmcu*) ; 
 int /*<<< orphan*/  dce_is_dmcu_initialized (struct dmcu*) ; 
 int /*<<< orphan*/  dm_write_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void dce_psr_wait_loop(
	struct dmcu *dmcu,
	unsigned int wait_loop_number)
{
	struct dce_dmcu *dmcu_dce = TO_DCE_DMCU(dmcu);
	union dce_dmcu_psr_config_data_wait_loop_reg1 masterCmdData1;

	if (dmcu->cached_wait_loop_number == wait_loop_number)
		return;

	/* DMCU is not running */
	if (!dce_is_dmcu_initialized(dmcu))
		return;

	/* waitDMCUReadyForCmd */
	REG_WAIT(MASTER_COMM_CNTL_REG, MASTER_COMM_INTERRUPT, 0, 1, 10000);

	masterCmdData1.u32 = 0;
	masterCmdData1.bits.wait_loop = wait_loop_number;
	dmcu->cached_wait_loop_number = wait_loop_number;
	dm_write_reg(dmcu->ctx, REG(MASTER_COMM_DATA_REG1), masterCmdData1.u32);

	/* setDMCUParam_Cmd */
	REG_UPDATE(MASTER_COMM_CMD_REG, MASTER_COMM_CMD_REG_BYTE0, PSR_SET_WAITLOOP);

	/* notifyDMCUMsg */
	REG_UPDATE(MASTER_COMM_CNTL_REG, MASTER_COMM_INTERRUPT, 1);
}