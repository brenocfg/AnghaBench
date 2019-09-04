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
struct input_pixel_processor {int dummy; } ;
struct dce_ipp {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/ * blue; int /*<<< orphan*/ * green; int /*<<< orphan*/ * red; } ;
struct dc_gamma {int num_entries; TYPE_1__ entries; } ;

/* Variables and functions */
 int /*<<< orphan*/  DCFE_MEM_PWR_CTRL ; 
 int /*<<< orphan*/  DCP_LUT_MEM_PWR_DIS ; 
 int /*<<< orphan*/  DC_LUT_CONTROL ; 
 int /*<<< orphan*/  DC_LUT_DATA_B_FORMAT ; 
 int /*<<< orphan*/  DC_LUT_DATA_G_FORMAT ; 
 int /*<<< orphan*/  DC_LUT_DATA_R_FORMAT ; 
 int /*<<< orphan*/  DC_LUT_RW_INDEX ; 
 int /*<<< orphan*/  DC_LUT_RW_MODE ; 
 int /*<<< orphan*/  DC_LUT_SEQ_COLOR ; 
 int /*<<< orphan*/  DC_LUT_WRITE_EN_MASK ; 
 int /*<<< orphan*/  GRPH_INPUT_GAMMA_MODE ; 
 int /*<<< orphan*/  GRPH_PRESCALE_BYPASS ; 
 int /*<<< orphan*/  INPUT_GAMMA_CONTROL ; 
 int /*<<< orphan*/  PRESCALE_GRPH_CONTROL ; 
 scalar_t__ REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  REG_SET_3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  REG_UPDATE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct dce_ipp* TO_DCE_IPP (struct input_pixel_processor*) ; 
 int dc_fixpt_round (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dce_ipp_program_input_lut(
	struct input_pixel_processor *ipp,
	const struct dc_gamma *gamma)
{
	int i;
	struct dce_ipp *ipp_dce = TO_DCE_IPP(ipp);

	/* power on LUT memory */
	if (REG(DCFE_MEM_PWR_CTRL))
		REG_SET(DCFE_MEM_PWR_CTRL, 0, DCP_LUT_MEM_PWR_DIS, 1);

	/* enable all */
	REG_SET(DC_LUT_WRITE_EN_MASK, 0, DC_LUT_WRITE_EN_MASK, 0x7);

	/* 256 entry mode */
	REG_UPDATE(DC_LUT_RW_MODE, DC_LUT_RW_MODE, 0);

	/* LUT-256, unsigned, integer, new u0.12 format */
	REG_SET_3(DC_LUT_CONTROL, 0,
		DC_LUT_DATA_R_FORMAT, 3,
		DC_LUT_DATA_G_FORMAT, 3,
		DC_LUT_DATA_B_FORMAT, 3);

	/* start from index 0 */
	REG_SET(DC_LUT_RW_INDEX, 0,
		DC_LUT_RW_INDEX, 0);

	for (i = 0; i < gamma->num_entries; i++) {
		REG_SET(DC_LUT_SEQ_COLOR, 0, DC_LUT_SEQ_COLOR,
				dc_fixpt_round(
					gamma->entries.red[i]));
		REG_SET(DC_LUT_SEQ_COLOR, 0, DC_LUT_SEQ_COLOR,
				dc_fixpt_round(
					gamma->entries.green[i]));
		REG_SET(DC_LUT_SEQ_COLOR, 0, DC_LUT_SEQ_COLOR,
				dc_fixpt_round(
					gamma->entries.blue[i]));
	}

	/* power off LUT memory */
	if (REG(DCFE_MEM_PWR_CTRL))
		REG_SET(DCFE_MEM_PWR_CTRL, 0, DCP_LUT_MEM_PWR_DIS, 0);

	/* bypass prescale, enable legacy LUT */
	REG_UPDATE(PRESCALE_GRPH_CONTROL, GRPH_PRESCALE_BYPASS, 1);
	REG_UPDATE(INPUT_GAMMA_CONTROL, GRPH_INPUT_GAMMA_MODE, 0);
}