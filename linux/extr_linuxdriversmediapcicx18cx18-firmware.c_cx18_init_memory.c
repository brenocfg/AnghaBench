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
struct cx18 {TYPE_2__* card; } ;
struct TYPE_3__ {int chip_config; int refresh; int timing1; int timing2; int tune_lane; int initial_emrs; } ;
struct TYPE_4__ {TYPE_1__ ddr; } ;

/* Variables and functions */
 int /*<<< orphan*/  CX18_DDR_BASE_63_ADDR ; 
 int /*<<< orphan*/  CX18_DDR_CHIP_CONFIG ; 
 int /*<<< orphan*/  CX18_DDR_INITIAL_EMRS ; 
 int /*<<< orphan*/  CX18_DDR_MB_PER_ROW_7 ; 
 int /*<<< orphan*/  CX18_DDR_POWER_REG ; 
 int /*<<< orphan*/  CX18_DDR_REFRESH ; 
 int /*<<< orphan*/  CX18_DDR_SOFT_RESET ; 
 int /*<<< orphan*/  CX18_DDR_TIMING1 ; 
 int /*<<< orphan*/  CX18_DDR_TIMING2 ; 
 int /*<<< orphan*/  CX18_DDR_TUNE_LANE ; 
 int /*<<< orphan*/  CX18_REG_BUS_TIMEOUT_EN ; 
 int /*<<< orphan*/  CX18_WMB_CLIENT02 ; 
 int /*<<< orphan*/  CX18_WMB_CLIENT05 ; 
 int /*<<< orphan*/  CX18_WMB_CLIENT06 ; 
 int /*<<< orphan*/  CX18_WMB_CLIENT07 ; 
 int /*<<< orphan*/  CX18_WMB_CLIENT09 ; 
 int /*<<< orphan*/  CX18_WMB_CLIENT10 ; 
 int /*<<< orphan*/  CX18_WMB_CLIENT11 ; 
 int /*<<< orphan*/  CX18_WMB_CLIENT12 ; 
 int /*<<< orphan*/  CX18_WMB_CLIENT13 ; 
 int /*<<< orphan*/  CX18_WMB_CLIENT14 ; 
 int /*<<< orphan*/  cx18_msleep_timeout (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cx18_write_reg (struct cx18*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cx18_write_reg_expect (struct cx18*,int,int /*<<< orphan*/ ,int,int) ; 

void cx18_init_memory(struct cx18 *cx)
{
	cx18_msleep_timeout(10, 0);
	cx18_write_reg_expect(cx, 0x00010000, CX18_DDR_SOFT_RESET,
				  0x00000000, 0x00010001);
	cx18_msleep_timeout(10, 0);

	cx18_write_reg(cx, cx->card->ddr.chip_config, CX18_DDR_CHIP_CONFIG);

	cx18_msleep_timeout(10, 0);

	cx18_write_reg(cx, cx->card->ddr.refresh, CX18_DDR_REFRESH);
	cx18_write_reg(cx, cx->card->ddr.timing1, CX18_DDR_TIMING1);
	cx18_write_reg(cx, cx->card->ddr.timing2, CX18_DDR_TIMING2);

	cx18_msleep_timeout(10, 0);

	/* Initialize DQS pad time */
	cx18_write_reg(cx, cx->card->ddr.tune_lane, CX18_DDR_TUNE_LANE);
	cx18_write_reg(cx, cx->card->ddr.initial_emrs, CX18_DDR_INITIAL_EMRS);

	cx18_msleep_timeout(10, 0);

	cx18_write_reg_expect(cx, 0x00020000, CX18_DDR_SOFT_RESET,
				  0x00000000, 0x00020002);
	cx18_msleep_timeout(10, 0);

	/* use power-down mode when idle */
	cx18_write_reg(cx, 0x00000010, CX18_DDR_POWER_REG);

	cx18_write_reg_expect(cx, 0x00010001, CX18_REG_BUS_TIMEOUT_EN,
				  0x00000001, 0x00010001);

	cx18_write_reg(cx, 0x48, CX18_DDR_MB_PER_ROW_7);
	cx18_write_reg(cx, 0xE0000, CX18_DDR_BASE_63_ADDR);

	cx18_write_reg(cx, 0x00000101, CX18_WMB_CLIENT02);  /* AO */
	cx18_write_reg(cx, 0x00000101, CX18_WMB_CLIENT09);  /* AI2 */
	cx18_write_reg(cx, 0x00000101, CX18_WMB_CLIENT05);  /* VIM1 */
	cx18_write_reg(cx, 0x00000101, CX18_WMB_CLIENT06);  /* AI1 */
	cx18_write_reg(cx, 0x00000101, CX18_WMB_CLIENT07);  /* 3D comb */
	cx18_write_reg(cx, 0x00000101, CX18_WMB_CLIENT10);  /* ME */
	cx18_write_reg(cx, 0x00000101, CX18_WMB_CLIENT12);  /* ENC */
	cx18_write_reg(cx, 0x00000101, CX18_WMB_CLIENT13);  /* PK */
	cx18_write_reg(cx, 0x00000101, CX18_WMB_CLIENT11);  /* RC */
	cx18_write_reg(cx, 0x00000101, CX18_WMB_CLIENT14);  /* AVO */
}