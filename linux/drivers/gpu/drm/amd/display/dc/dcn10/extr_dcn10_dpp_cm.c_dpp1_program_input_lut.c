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
typedef  int /*<<< orphan*/  uint32_t ;
struct dpp {int dummy; } ;
struct dcn10_dpp {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/ * blue; int /*<<< orphan*/ * green; int /*<<< orphan*/ * red; } ;
struct dc_gamma {int num_entries; TYPE_1__ entries; } ;

/* Variables and functions */
 int /*<<< orphan*/  CM_IGAM_CONTROL ; 
 int /*<<< orphan*/  CM_IGAM_INPUT_FORMAT ; 
 int /*<<< orphan*/  CM_IGAM_LUT_FORMAT_B ; 
 int /*<<< orphan*/  CM_IGAM_LUT_FORMAT_G ; 
 int /*<<< orphan*/  CM_IGAM_LUT_FORMAT_R ; 
 int /*<<< orphan*/  CM_IGAM_LUT_MODE ; 
 int /*<<< orphan*/  CM_IGAM_LUT_RW_CONTROL ; 
 int /*<<< orphan*/  CM_IGAM_LUT_RW_INDEX ; 
 int /*<<< orphan*/  CM_IGAM_LUT_RW_MODE ; 
 int /*<<< orphan*/  CM_IGAM_LUT_SEL ; 
 int /*<<< orphan*/  CM_IGAM_LUT_SEQ_COLOR ; 
 int /*<<< orphan*/  CM_IGAM_LUT_WRITE_EN_MASK ; 
 int /*<<< orphan*/  CM_MEM_PWR_CTRL ; 
 int /*<<< orphan*/  REG_GET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  REG_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  REG_UPDATE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  REG_UPDATE_3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SHARED_MEM_PWR_DIS ; 
 struct dcn10_dpp* TO_DCN10_DPP (struct dpp*) ; 
 int dc_fixpt_round (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dpp1_enable_cm_block (struct dpp*) ; 
 int /*<<< orphan*/  dpp1_ingamma_ram_inuse (struct dpp*,int*) ; 

void dpp1_program_input_lut(
		struct dpp *dpp_base,
		const struct dc_gamma *gamma)
{
	int i;
	struct dcn10_dpp *dpp = TO_DCN10_DPP(dpp_base);
	bool rama_occupied = false;
	uint32_t ram_num;
	// Power on LUT memory.
	REG_SET(CM_MEM_PWR_CTRL, 0, SHARED_MEM_PWR_DIS, 1);
	dpp1_enable_cm_block(dpp_base);
	// Determine whether to use RAM A or RAM B
	dpp1_ingamma_ram_inuse(dpp_base, &rama_occupied);
	if (!rama_occupied)
		REG_UPDATE(CM_IGAM_LUT_RW_CONTROL, CM_IGAM_LUT_SEL, 0);
	else
		REG_UPDATE(CM_IGAM_LUT_RW_CONTROL, CM_IGAM_LUT_SEL, 1);
	// RW mode is 256-entry LUT
	REG_UPDATE(CM_IGAM_LUT_RW_CONTROL, CM_IGAM_LUT_RW_MODE, 0);
	// IGAM Input format should be 8 bits per channel.
	REG_UPDATE(CM_IGAM_CONTROL, CM_IGAM_INPUT_FORMAT, 0);
	// Do not mask any R,G,B values
	REG_UPDATE(CM_IGAM_LUT_RW_CONTROL, CM_IGAM_LUT_WRITE_EN_MASK, 7);
	// LUT-256, unsigned, integer, new u0.12 format
	REG_UPDATE_3(
		CM_IGAM_CONTROL,
		CM_IGAM_LUT_FORMAT_R, 3,
		CM_IGAM_LUT_FORMAT_G, 3,
		CM_IGAM_LUT_FORMAT_B, 3);
	// Start at index 0 of IGAM LUT
	REG_UPDATE(CM_IGAM_LUT_RW_INDEX, CM_IGAM_LUT_RW_INDEX, 0);
	for (i = 0; i < gamma->num_entries; i++) {
		REG_SET(CM_IGAM_LUT_SEQ_COLOR, 0, CM_IGAM_LUT_SEQ_COLOR,
				dc_fixpt_round(
					gamma->entries.red[i]));
		REG_SET(CM_IGAM_LUT_SEQ_COLOR, 0, CM_IGAM_LUT_SEQ_COLOR,
				dc_fixpt_round(
					gamma->entries.green[i]));
		REG_SET(CM_IGAM_LUT_SEQ_COLOR, 0, CM_IGAM_LUT_SEQ_COLOR,
				dc_fixpt_round(
					gamma->entries.blue[i]));
	}
	// Power off LUT memory
	REG_SET(CM_MEM_PWR_CTRL, 0, SHARED_MEM_PWR_DIS, 0);
	// Enable IGAM LUT on ram we just wrote to. 2 => RAMA, 3 => RAMB
	REG_UPDATE(CM_IGAM_CONTROL, CM_IGAM_LUT_MODE, rama_occupied ? 3 : 2);
	REG_GET(CM_IGAM_CONTROL, CM_IGAM_LUT_MODE, &ram_num);
}