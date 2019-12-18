#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  psr_level; } ;
union dce_dmcu_psr_config_data_reg3 {scalar_t__ u32All; TYPE_4__ bits; } ;
struct TYPE_10__ {int /*<<< orphan*/  num_of_controllers; int /*<<< orphan*/  smu_phy_id; int /*<<< orphan*/  frame_delay; int /*<<< orphan*/  skip_wait_for_pll_lock; int /*<<< orphan*/  dig_be; int /*<<< orphan*/  dig_fe; } ;
union dce_dmcu_psr_config_data_reg2 {scalar_t__ u32All; TYPE_3__ bits; } ;
struct TYPE_9__ {int dcp_sel; int /*<<< orphan*/  aux_repeat; int /*<<< orphan*/  aux_chan; int /*<<< orphan*/  frame_cap_ind; int /*<<< orphan*/  phy_type; int /*<<< orphan*/  dp_port_num; int /*<<< orphan*/  rfb_update_auto_en; int /*<<< orphan*/  hyst_lines; int /*<<< orphan*/  timehyst_frames; } ;
union dce_dmcu_psr_config_data_reg1 {scalar_t__ u32All; TYPE_2__ bits; } ;
struct TYPE_12__ {int /*<<< orphan*/  u32all; } ;
struct psr_context {int controllerId; TYPE_5__ psr_level; int /*<<< orphan*/  numberOfControllers; int /*<<< orphan*/  smuPhyId; int /*<<< orphan*/  frame_delay; int /*<<< orphan*/  skipPsrWaitForPllLock; int /*<<< orphan*/  transmitterId; int /*<<< orphan*/  engineId; int /*<<< orphan*/  aux_repeats; int /*<<< orphan*/  channel; int /*<<< orphan*/  psrFrameCaptureIndicationReq; int /*<<< orphan*/  phyType; int /*<<< orphan*/  rfb_update_auto_en; int /*<<< orphan*/  hyst_lines; int /*<<< orphan*/  timehyst_frames; int /*<<< orphan*/  sdpTransmitLineNumDeadline; int /*<<< orphan*/  psrExitLinkTrainingRequired; } ;
struct dmcu {int /*<<< orphan*/  ctx; } ;
struct dce_dmcu {int dummy; } ;
struct dc_link {TYPE_6__* link_enc; } ;
struct TYPE_13__ {TYPE_1__* funcs; } ;
struct TYPE_8__ {int /*<<< orphan*/  (* psr_program_secondary_packet ) (TYPE_6__*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* psr_program_dp_dphy_fast_training ) (TYPE_6__*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DMCU_INTERRUPT_TO_UC_EN_MASK ; 
 int /*<<< orphan*/  MASTER_COMM_CMD_REG ; 
 int /*<<< orphan*/  MASTER_COMM_CMD_REG_BYTE0 ; 
 int /*<<< orphan*/  MASTER_COMM_CNTL_REG ; 
 int /*<<< orphan*/  MASTER_COMM_DATA_REG1 ; 
 int /*<<< orphan*/  MASTER_COMM_DATA_REG2 ; 
 int /*<<< orphan*/  MASTER_COMM_DATA_REG3 ; 
 int /*<<< orphan*/  MASTER_COMM_INTERRUPT ; 
 int PSR_SET ; 
 int /*<<< orphan*/  REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_UPDATE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  REG_UPDATE_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_WAIT (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  STATIC_SCREEN1_INT_TO_UC_EN ; 
 int /*<<< orphan*/  STATIC_SCREEN2_INT_TO_UC_EN ; 
 int /*<<< orphan*/  STATIC_SCREEN3_INT_TO_UC_EN ; 
 int /*<<< orphan*/  STATIC_SCREEN4_INT_TO_UC_EN ; 
 struct dce_dmcu* TO_DCE_DMCU (struct dmcu*) ; 
 int /*<<< orphan*/  dm_write_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  stub1 (TYPE_6__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (TYPE_6__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool dce_dmcu_setup_psr(struct dmcu *dmcu,
		struct dc_link *link,
		struct psr_context *psr_context)
{
	struct dce_dmcu *dmcu_dce = TO_DCE_DMCU(dmcu);

	unsigned int dmcu_max_retry_on_wait_reg_ready = 801;
	unsigned int dmcu_wait_reg_ready_interval = 100;

	union dce_dmcu_psr_config_data_reg1 masterCmdData1;
	union dce_dmcu_psr_config_data_reg2 masterCmdData2;
	union dce_dmcu_psr_config_data_reg3 masterCmdData3;

	link->link_enc->funcs->psr_program_dp_dphy_fast_training(link->link_enc,
			psr_context->psrExitLinkTrainingRequired);

	/* Enable static screen interrupts for PSR supported display */
	/* Disable the interrupt coming from other displays. */
	REG_UPDATE_4(DMCU_INTERRUPT_TO_UC_EN_MASK,
			STATIC_SCREEN1_INT_TO_UC_EN, 0,
			STATIC_SCREEN2_INT_TO_UC_EN, 0,
			STATIC_SCREEN3_INT_TO_UC_EN, 0,
			STATIC_SCREEN4_INT_TO_UC_EN, 0);

	switch (psr_context->controllerId) {
	/* Driver uses case 1 for unconfigured */
	case 1:
		REG_UPDATE(DMCU_INTERRUPT_TO_UC_EN_MASK,
				STATIC_SCREEN1_INT_TO_UC_EN, 1);
		break;
	case 2:
		REG_UPDATE(DMCU_INTERRUPT_TO_UC_EN_MASK,
				STATIC_SCREEN2_INT_TO_UC_EN, 1);
		break;
	case 3:
		REG_UPDATE(DMCU_INTERRUPT_TO_UC_EN_MASK,
				STATIC_SCREEN3_INT_TO_UC_EN, 1);
		break;
	case 4:
		REG_UPDATE(DMCU_INTERRUPT_TO_UC_EN_MASK,
				STATIC_SCREEN4_INT_TO_UC_EN, 1);
		break;
	case 5:
		/* CZ/NL only has 4 CRTC!!
		 * really valid.
		 * There is no interrupt enable mask for these instances.
		 */
		break;
	case 6:
		/* CZ/NL only has 4 CRTC!!
		 * These are here because they are defined in HW regspec,
		 * but not really valid. There is no interrupt enable mask
		 * for these instances.
		 */
		break;
	default:
		REG_UPDATE(DMCU_INTERRUPT_TO_UC_EN_MASK,
				STATIC_SCREEN1_INT_TO_UC_EN, 1);
		break;
	}

	link->link_enc->funcs->psr_program_secondary_packet(link->link_enc,
			psr_context->sdpTransmitLineNumDeadline);

	/* waitDMCUReadyForCmd */
	REG_WAIT(MASTER_COMM_CNTL_REG, MASTER_COMM_INTERRUPT, 0,
					dmcu_wait_reg_ready_interval,
					dmcu_max_retry_on_wait_reg_ready);

	/* setDMCUParam_PSRHostConfigData */
	masterCmdData1.u32All = 0;
	masterCmdData1.bits.timehyst_frames = psr_context->timehyst_frames;
	masterCmdData1.bits.hyst_lines = psr_context->hyst_lines;
	masterCmdData1.bits.rfb_update_auto_en =
			psr_context->rfb_update_auto_en;
	masterCmdData1.bits.dp_port_num = psr_context->transmitterId;
	masterCmdData1.bits.dcp_sel = psr_context->controllerId;
	masterCmdData1.bits.phy_type  = psr_context->phyType;
	masterCmdData1.bits.frame_cap_ind =
			psr_context->psrFrameCaptureIndicationReq;
	masterCmdData1.bits.aux_chan = psr_context->channel;
	masterCmdData1.bits.aux_repeat = psr_context->aux_repeats;
	dm_write_reg(dmcu->ctx, REG(MASTER_COMM_DATA_REG1),
					masterCmdData1.u32All);

	masterCmdData2.u32All = 0;
	masterCmdData2.bits.dig_fe = psr_context->engineId;
	masterCmdData2.bits.dig_be = psr_context->transmitterId;
	masterCmdData2.bits.skip_wait_for_pll_lock =
			psr_context->skipPsrWaitForPllLock;
	masterCmdData2.bits.frame_delay = psr_context->frame_delay;
	masterCmdData2.bits.smu_phy_id = psr_context->smuPhyId;
	masterCmdData2.bits.num_of_controllers =
			psr_context->numberOfControllers;
	dm_write_reg(dmcu->ctx, REG(MASTER_COMM_DATA_REG2),
			masterCmdData2.u32All);

	masterCmdData3.u32All = 0;
	masterCmdData3.bits.psr_level = psr_context->psr_level.u32all;
	dm_write_reg(dmcu->ctx, REG(MASTER_COMM_DATA_REG3),
			masterCmdData3.u32All);

	/* setDMCUParam_Cmd */
	REG_UPDATE(MASTER_COMM_CMD_REG,
			MASTER_COMM_CMD_REG_BYTE0, PSR_SET);

	/* notifyDMCUMsg */
	REG_UPDATE(MASTER_COMM_CNTL_REG, MASTER_COMM_INTERRUPT, 1);

	return true;
}