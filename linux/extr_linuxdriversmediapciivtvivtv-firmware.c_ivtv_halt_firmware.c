#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * mbox; } ;
struct TYPE_3__ {int /*<<< orphan*/  mbox; } ;
struct ivtv {scalar_t__ has_cx23415; TYPE_2__ dec_mbox; TYPE_1__ enc_mbox; } ;

/* Variables and functions */
 int /*<<< orphan*/  CX2341X_DEC_HALT_FW ; 
 int /*<<< orphan*/  CX2341X_ENC_HALT_FW ; 
 int /*<<< orphan*/  IVTV_CMD_AO_STOP ; 
 int /*<<< orphan*/  IVTV_CMD_APU_PING ; 
 int /*<<< orphan*/  IVTV_CMD_HW_BLOCKS_RST ; 
 int /*<<< orphan*/  IVTV_CMD_SDRAM_PRECHARGE_INIT ; 
 int /*<<< orphan*/  IVTV_CMD_SDRAM_REFRESH_INIT ; 
 int /*<<< orphan*/  IVTV_CMD_SPU_STOP ; 
 int /*<<< orphan*/  IVTV_CMD_VDM_STOP ; 
 int /*<<< orphan*/  IVTV_CMD_VPU_STOP15 ; 
 int /*<<< orphan*/  IVTV_CMD_VPU_STOP16 ; 
 int /*<<< orphan*/  IVTV_DEBUG_INFO (char*,...) ; 
 int /*<<< orphan*/  IVTV_REG_AO ; 
 int /*<<< orphan*/  IVTV_REG_APU ; 
 int /*<<< orphan*/  IVTV_REG_DEC_SDRAM_PRECHARGE ; 
 int /*<<< orphan*/  IVTV_REG_DEC_SDRAM_REFRESH ; 
 int /*<<< orphan*/  IVTV_REG_ENC_SDRAM_PRECHARGE ; 
 int /*<<< orphan*/  IVTV_REG_ENC_SDRAM_REFRESH ; 
 int /*<<< orphan*/  IVTV_REG_HW_BLOCKS ; 
 int /*<<< orphan*/  IVTV_REG_SPU ; 
 int /*<<< orphan*/  IVTV_REG_VDM ; 
 int /*<<< orphan*/  IVTV_REG_VPU ; 
 int IVTV_SDRAM_SLEEPTIME ; 
 int /*<<< orphan*/  ivtv_msleep_timeout (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ivtv_vapi (struct ivtv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void ivtv_halt_firmware(struct ivtv *itv)
{
	IVTV_DEBUG_INFO("Preparing for firmware halt.\n");
	if (itv->has_cx23415 && itv->dec_mbox.mbox)
		ivtv_vapi(itv, CX2341X_DEC_HALT_FW, 0);
	if (itv->enc_mbox.mbox)
		ivtv_vapi(itv, CX2341X_ENC_HALT_FW, 0);

	ivtv_msleep_timeout(10, 0);
	itv->enc_mbox.mbox = itv->dec_mbox.mbox = NULL;

	IVTV_DEBUG_INFO("Stopping VDM\n");
	write_reg(IVTV_CMD_VDM_STOP, IVTV_REG_VDM);

	IVTV_DEBUG_INFO("Stopping AO\n");
	write_reg(IVTV_CMD_AO_STOP, IVTV_REG_AO);

	IVTV_DEBUG_INFO("pinging (?) APU\n");
	write_reg(IVTV_CMD_APU_PING, IVTV_REG_APU);

	IVTV_DEBUG_INFO("Stopping VPU\n");
	if (!itv->has_cx23415)
		write_reg(IVTV_CMD_VPU_STOP16, IVTV_REG_VPU);
	else
		write_reg(IVTV_CMD_VPU_STOP15, IVTV_REG_VPU);

	IVTV_DEBUG_INFO("Resetting Hw Blocks\n");
	write_reg(IVTV_CMD_HW_BLOCKS_RST, IVTV_REG_HW_BLOCKS);

	IVTV_DEBUG_INFO("Stopping SPU\n");
	write_reg(IVTV_CMD_SPU_STOP, IVTV_REG_SPU);

	ivtv_msleep_timeout(10, 0);

	IVTV_DEBUG_INFO("init Encoder SDRAM pre-charge\n");
	write_reg(IVTV_CMD_SDRAM_PRECHARGE_INIT, IVTV_REG_ENC_SDRAM_PRECHARGE);

	IVTV_DEBUG_INFO("init Encoder SDRAM refresh to 1us\n");
	write_reg(IVTV_CMD_SDRAM_REFRESH_INIT, IVTV_REG_ENC_SDRAM_REFRESH);

	if (itv->has_cx23415) {
		IVTV_DEBUG_INFO("init Decoder SDRAM pre-charge\n");
		write_reg(IVTV_CMD_SDRAM_PRECHARGE_INIT, IVTV_REG_DEC_SDRAM_PRECHARGE);

		IVTV_DEBUG_INFO("init Decoder SDRAM refresh to 1us\n");
		write_reg(IVTV_CMD_SDRAM_REFRESH_INIT, IVTV_REG_DEC_SDRAM_REFRESH);
	}

	IVTV_DEBUG_INFO("Sleeping for %dms\n", IVTV_SDRAM_SLEEPTIME);
	ivtv_msleep_timeout(IVTV_SDRAM_SLEEPTIME, 0);
}