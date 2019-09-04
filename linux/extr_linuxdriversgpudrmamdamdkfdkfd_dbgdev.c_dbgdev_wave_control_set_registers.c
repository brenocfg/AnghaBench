#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int check_vmid; int /*<<< orphan*/  trap_id; int /*<<< orphan*/  cmd; void* mode; int /*<<< orphan*/  wave_id; int /*<<< orphan*/  simd_id; } ;
union SQ_CMD_BITS {TYPE_5__ bits; scalar_t__ u32All; } ;
struct TYPE_8__ {int sh_broadcast_writes; int se_broadcast_writes; int instance_broadcast_writes; int /*<<< orphan*/  instance_index; int /*<<< orphan*/  se_index; int /*<<< orphan*/  sh_index; } ;
union GRBM_GFX_INDEX_BITS {TYPE_3__ bits; scalar_t__ u32All; } ;
struct TYPE_9__ {int /*<<< orphan*/  HSACU; int /*<<< orphan*/  ShaderEngine; int /*<<< orphan*/  ShaderArray; int /*<<< orphan*/  WaveId; int /*<<< orphan*/  SIMD; } ;
struct HsaDbgWaveMsgAMDGen2 {TYPE_4__ ui32; } ;
struct TYPE_6__ {struct HsaDbgWaveMsgAMDGen2 WaveMsgInfoGen2; } ;
struct TYPE_7__ {TYPE_1__ DbgWaveMsg; } ;
struct dbg_wave_control_info {int mode; int operand; int /*<<< orphan*/  trapId; TYPE_2__ dbgWave_msg; } ;

/* Variables and functions */
 int EINVAL ; 
#define  HSA_DBG_WAVEMODE_BROADCAST_PROCESS 135 
#define  HSA_DBG_WAVEMODE_BROADCAST_PROCESS_CU 134 
#define  HSA_DBG_WAVEMODE_SINGLE 133 
#define  HSA_DBG_WAVEOP_DEBUG 132 
#define  HSA_DBG_WAVEOP_HALT 131 
#define  HSA_DBG_WAVEOP_KILL 130 
#define  HSA_DBG_WAVEOP_RESUME 129 
#define  HSA_DBG_WAVEOP_TRAP 128 
 int /*<<< orphan*/  MAX_TRAPID ; 
 int /*<<< orphan*/  SQ_IND_CMD_CMD_DEBUG ; 
 int /*<<< orphan*/  SQ_IND_CMD_CMD_HALT ; 
 int /*<<< orphan*/  SQ_IND_CMD_CMD_KILL ; 
 int /*<<< orphan*/  SQ_IND_CMD_CMD_RESUME ; 
 int /*<<< orphan*/  SQ_IND_CMD_CMD_TRAP ; 
 void* SQ_IND_CMD_MODE_BROADCAST ; 
 void* SQ_IND_CMD_MODE_SINGLE ; 

__attribute__((used)) static int dbgdev_wave_control_set_registers(
				struct dbg_wave_control_info *wac_info,
				union SQ_CMD_BITS *in_reg_sq_cmd,
				union GRBM_GFX_INDEX_BITS *in_reg_gfx_index)
{
	int status = 0;
	union SQ_CMD_BITS reg_sq_cmd;
	union GRBM_GFX_INDEX_BITS reg_gfx_index;
	struct HsaDbgWaveMsgAMDGen2 *pMsg;

	reg_sq_cmd.u32All = 0;
	reg_gfx_index.u32All = 0;
	pMsg = &wac_info->dbgWave_msg.DbgWaveMsg.WaveMsgInfoGen2;

	switch (wac_info->mode) {
	/* Send command to single wave */
	case HSA_DBG_WAVEMODE_SINGLE:
		/*
		 * Limit access to the process waves only,
		 * by setting vmid check
		 */
		reg_sq_cmd.bits.check_vmid = 1;
		reg_sq_cmd.bits.simd_id = pMsg->ui32.SIMD;
		reg_sq_cmd.bits.wave_id = pMsg->ui32.WaveId;
		reg_sq_cmd.bits.mode = SQ_IND_CMD_MODE_SINGLE;

		reg_gfx_index.bits.sh_index = pMsg->ui32.ShaderArray;
		reg_gfx_index.bits.se_index = pMsg->ui32.ShaderEngine;
		reg_gfx_index.bits.instance_index = pMsg->ui32.HSACU;

		break;

	/* Send command to all waves with matching VMID */
	case HSA_DBG_WAVEMODE_BROADCAST_PROCESS:

		reg_gfx_index.bits.sh_broadcast_writes = 1;
		reg_gfx_index.bits.se_broadcast_writes = 1;
		reg_gfx_index.bits.instance_broadcast_writes = 1;

		reg_sq_cmd.bits.mode = SQ_IND_CMD_MODE_BROADCAST;

		break;

	/* Send command to all CU waves with matching VMID */
	case HSA_DBG_WAVEMODE_BROADCAST_PROCESS_CU:

		reg_sq_cmd.bits.check_vmid = 1;
		reg_sq_cmd.bits.mode = SQ_IND_CMD_MODE_BROADCAST;

		reg_gfx_index.bits.sh_index = pMsg->ui32.ShaderArray;
		reg_gfx_index.bits.se_index = pMsg->ui32.ShaderEngine;
		reg_gfx_index.bits.instance_index = pMsg->ui32.HSACU;

		break;

	default:
		return -EINVAL;
	}

	switch (wac_info->operand) {
	case HSA_DBG_WAVEOP_HALT:
		reg_sq_cmd.bits.cmd = SQ_IND_CMD_CMD_HALT;
		break;

	case HSA_DBG_WAVEOP_RESUME:
		reg_sq_cmd.bits.cmd = SQ_IND_CMD_CMD_RESUME;
		break;

	case HSA_DBG_WAVEOP_KILL:
		reg_sq_cmd.bits.cmd = SQ_IND_CMD_CMD_KILL;
		break;

	case HSA_DBG_WAVEOP_DEBUG:
		reg_sq_cmd.bits.cmd = SQ_IND_CMD_CMD_DEBUG;
		break;

	case HSA_DBG_WAVEOP_TRAP:
		if (wac_info->trapId < MAX_TRAPID) {
			reg_sq_cmd.bits.cmd = SQ_IND_CMD_CMD_TRAP;
			reg_sq_cmd.bits.trap_id = wac_info->trapId;
		} else {
			status = -EINVAL;
		}
		break;

	default:
		status = -EINVAL;
		break;
	}

	if (status == 0) {
		*in_reg_sq_cmd = reg_sq_cmd;
		*in_reg_gfx_index = reg_gfx_index;
	}

	return status;
}