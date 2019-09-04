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
struct a6xx_gmu {int dummy; } ;

/* Variables and functions */
 int BIT (int) ; 
 scalar_t__ REG_A6XX_GPU_RSCC_RSC_STATUS0_DRV0 ; 
 scalar_t__ REG_A6XX_PDC_GPU_ENABLE_PDC ; 
 scalar_t__ REG_A6XX_PDC_GPU_SEQ_MEM_0 ; 
 scalar_t__ REG_A6XX_PDC_GPU_SEQ_START_ADDR ; 
 scalar_t__ REG_A6XX_PDC_GPU_TCS1_CMD0_ADDR ; 
 scalar_t__ REG_A6XX_PDC_GPU_TCS1_CMD0_DATA ; 
 scalar_t__ REG_A6XX_PDC_GPU_TCS1_CMD0_MSGID ; 
 scalar_t__ REG_A6XX_PDC_GPU_TCS1_CMD_ENABLE_BANK ; 
 scalar_t__ REG_A6XX_PDC_GPU_TCS1_CMD_WAIT_FOR_CMPL_BANK ; 
 scalar_t__ REG_A6XX_PDC_GPU_TCS1_CONTROL ; 
 scalar_t__ REG_A6XX_PDC_GPU_TCS3_CMD0_ADDR ; 
 scalar_t__ REG_A6XX_PDC_GPU_TCS3_CMD0_DATA ; 
 scalar_t__ REG_A6XX_PDC_GPU_TCS3_CMD0_MSGID ; 
 scalar_t__ REG_A6XX_PDC_GPU_TCS3_CMD_ENABLE_BANK ; 
 scalar_t__ REG_A6XX_PDC_GPU_TCS3_CMD_WAIT_FOR_CMPL_BANK ; 
 scalar_t__ REG_A6XX_PDC_GPU_TCS3_CONTROL ; 
 scalar_t__ REG_A6XX_RSCC_HIDDEN_TCS_CMD0_ADDR ; 
 scalar_t__ REG_A6XX_RSCC_HIDDEN_TCS_CMD0_DATA ; 
 scalar_t__ REG_A6XX_RSCC_OVERRIDE_START_ADDR ; 
 scalar_t__ REG_A6XX_RSCC_PDC_MATCH_VALUE_HI ; 
 scalar_t__ REG_A6XX_RSCC_PDC_MATCH_VALUE_LO ; 
 scalar_t__ REG_A6XX_RSCC_PDC_SEQ_START_ADDR ; 
 scalar_t__ REG_A6XX_RSCC_PDC_SLAVE_ID_DRV0 ; 
 scalar_t__ REG_A6XX_RSCC_SEQ_MEM_0_DRV0 ; 
 int /*<<< orphan*/  gmu_write (struct a6xx_gmu*,scalar_t__,int) ; 
 int /*<<< orphan*/  pdc_write (struct a6xx_gmu*,scalar_t__,int) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static void a6xx_gmu_rpmh_init(struct a6xx_gmu *gmu)
{
	/* Disable SDE clock gating */
	gmu_write(gmu, REG_A6XX_GPU_RSCC_RSC_STATUS0_DRV0, BIT(24));

	/* Setup RSC PDC handshake for sleep and wakeup */
	gmu_write(gmu, REG_A6XX_RSCC_PDC_SLAVE_ID_DRV0, 1);
	gmu_write(gmu, REG_A6XX_RSCC_HIDDEN_TCS_CMD0_DATA, 0);
	gmu_write(gmu, REG_A6XX_RSCC_HIDDEN_TCS_CMD0_ADDR, 0);
	gmu_write(gmu, REG_A6XX_RSCC_HIDDEN_TCS_CMD0_DATA + 2, 0);
	gmu_write(gmu, REG_A6XX_RSCC_HIDDEN_TCS_CMD0_ADDR + 2, 0);
	gmu_write(gmu, REG_A6XX_RSCC_HIDDEN_TCS_CMD0_DATA + 4, 0x80000000);
	gmu_write(gmu, REG_A6XX_RSCC_HIDDEN_TCS_CMD0_ADDR + 4, 0);
	gmu_write(gmu, REG_A6XX_RSCC_OVERRIDE_START_ADDR, 0);
	gmu_write(gmu, REG_A6XX_RSCC_PDC_SEQ_START_ADDR, 0x4520);
	gmu_write(gmu, REG_A6XX_RSCC_PDC_MATCH_VALUE_LO, 0x4510);
	gmu_write(gmu, REG_A6XX_RSCC_PDC_MATCH_VALUE_HI, 0x4514);

	/* Load RSC sequencer uCode for sleep and wakeup */
	gmu_write(gmu, REG_A6XX_RSCC_SEQ_MEM_0_DRV0, 0xa7a506a0);
	gmu_write(gmu, REG_A6XX_RSCC_SEQ_MEM_0_DRV0 + 1, 0xa1e6a6e7);
	gmu_write(gmu, REG_A6XX_RSCC_SEQ_MEM_0_DRV0 + 2, 0xa2e081e1);
	gmu_write(gmu, REG_A6XX_RSCC_SEQ_MEM_0_DRV0 + 3, 0xe9a982e2);
	gmu_write(gmu, REG_A6XX_RSCC_SEQ_MEM_0_DRV0 + 4, 0x0020e8a8);

	/* Load PDC sequencer uCode for power up and power down sequence */
	pdc_write(gmu, REG_A6XX_PDC_GPU_SEQ_MEM_0, 0xfebea1e1);
	pdc_write(gmu, REG_A6XX_PDC_GPU_SEQ_MEM_0 + 1, 0xa5a4a3a2);
	pdc_write(gmu, REG_A6XX_PDC_GPU_SEQ_MEM_0 + 2, 0x8382a6e0);
	pdc_write(gmu, REG_A6XX_PDC_GPU_SEQ_MEM_0 + 3, 0xbce3e284);
	pdc_write(gmu, REG_A6XX_PDC_GPU_SEQ_MEM_0 + 4, 0x002081fc);

	/* Set TCS commands used by PDC sequence for low power modes */
	pdc_write(gmu, REG_A6XX_PDC_GPU_TCS1_CMD_ENABLE_BANK, 7);
	pdc_write(gmu, REG_A6XX_PDC_GPU_TCS1_CMD_WAIT_FOR_CMPL_BANK, 0);
	pdc_write(gmu, REG_A6XX_PDC_GPU_TCS1_CONTROL, 0);
	pdc_write(gmu, REG_A6XX_PDC_GPU_TCS1_CMD0_MSGID, 0x10108);
	pdc_write(gmu, REG_A6XX_PDC_GPU_TCS1_CMD0_ADDR, 0x30010);
	pdc_write(gmu, REG_A6XX_PDC_GPU_TCS1_CMD0_DATA, 1);
	pdc_write(gmu, REG_A6XX_PDC_GPU_TCS1_CMD0_MSGID + 4, 0x10108);
	pdc_write(gmu, REG_A6XX_PDC_GPU_TCS1_CMD0_ADDR + 4, 0x30000);
	pdc_write(gmu, REG_A6XX_PDC_GPU_TCS1_CMD0_DATA + 4, 0x0);
	pdc_write(gmu, REG_A6XX_PDC_GPU_TCS1_CMD0_MSGID + 8, 0x10108);
	pdc_write(gmu, REG_A6XX_PDC_GPU_TCS1_CMD0_ADDR + 8, 0x30080);
	pdc_write(gmu, REG_A6XX_PDC_GPU_TCS1_CMD0_DATA + 8, 0x0);
	pdc_write(gmu, REG_A6XX_PDC_GPU_TCS3_CMD_ENABLE_BANK, 7);
	pdc_write(gmu, REG_A6XX_PDC_GPU_TCS3_CMD_WAIT_FOR_CMPL_BANK, 0);
	pdc_write(gmu, REG_A6XX_PDC_GPU_TCS3_CONTROL, 0);
	pdc_write(gmu, REG_A6XX_PDC_GPU_TCS3_CMD0_MSGID, 0x10108);
	pdc_write(gmu, REG_A6XX_PDC_GPU_TCS3_CMD0_ADDR, 0x30010);
	pdc_write(gmu, REG_A6XX_PDC_GPU_TCS3_CMD0_DATA, 2);
	pdc_write(gmu, REG_A6XX_PDC_GPU_TCS3_CMD0_MSGID + 4, 0x10108);
	pdc_write(gmu, REG_A6XX_PDC_GPU_TCS3_CMD0_ADDR + 4, 0x30000);
	pdc_write(gmu, REG_A6XX_PDC_GPU_TCS3_CMD0_DATA + 4, 0x3);
	pdc_write(gmu, REG_A6XX_PDC_GPU_TCS3_CMD0_MSGID + 8, 0x10108);
	pdc_write(gmu, REG_A6XX_PDC_GPU_TCS3_CMD0_ADDR + 8, 0x30080);
	pdc_write(gmu, REG_A6XX_PDC_GPU_TCS3_CMD0_DATA + 8, 0x3);

	/* Setup GPU PDC */
	pdc_write(gmu, REG_A6XX_PDC_GPU_SEQ_START_ADDR, 0);
	pdc_write(gmu, REG_A6XX_PDC_GPU_ENABLE_PDC, 0x80000001);

	/* ensure no writes happen before the uCode is fully written */
	wmb();
}