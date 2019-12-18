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
struct mxl111sf_state {int dummy; } ;
struct mxl111sf_reg_ctrl_info {int member_0; int member_1; int member_2; } ;

/* Variables and functions */
 int mxl111sf_ctrl_program_regs (struct mxl111sf_state*,struct mxl111sf_reg_ctrl_info*) ; 
 int /*<<< orphan*/  mxl_debug (char*) ; 

int mxl111sf_init_tuner_demod(struct mxl111sf_state *state)
{
	struct mxl111sf_reg_ctrl_info mxl_111_overwrite_default[] = {
		{0x07, 0xff, 0x0c},
		{0x58, 0xff, 0x9d},
		{0x09, 0xff, 0x00},
		{0x06, 0xff, 0x06},
		{0xc8, 0xff, 0x40}, /* ED_LE_WIN_OLD = 0 */
		{0x8d, 0x01, 0x01}, /* NEGATE_Q */
		{0x32, 0xff, 0xac}, /* DIG_RFREFSELECT = 12 */
		{0x42, 0xff, 0x43}, /* DIG_REG_AMP = 4 */
		{0x74, 0xff, 0xc4}, /* SSPUR_FS_PRIO = 4 */
		{0x71, 0xff, 0xe6}, /* SPUR_ROT_PRIO_VAL = 1 */
		{0x83, 0xff, 0x64}, /* INF_FILT1_THD_SC = 100 */
		{0x85, 0xff, 0x64}, /* INF_FILT2_THD_SC = 100 */
		{0x88, 0xff, 0xf0}, /* INF_THD = 240 */
		{0x6f, 0xf0, 0xb0}, /* DFE_DLY = 11 */
		{0x00, 0xff, 0x01}, /* Change to page 1 */
		{0x81, 0xff, 0x11}, /* DSM_FERR_BYPASS = 1 */
		{0xf4, 0xff, 0x07}, /* DIG_FREQ_CORR = 1 */
		{0xd4, 0x1f, 0x0f}, /* SPUR_TEST_NOISE_TH = 15 */
		{0xd6, 0xff, 0x0c}, /* SPUR_TEST_NOISE_PAPR = 12 */
		{0x00, 0xff, 0x00}, /* Change to page 0 */
		{0,    0,    0}
	};

	mxl_debug("()");

	return mxl111sf_ctrl_program_regs(state, mxl_111_overwrite_default);
}