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
typedef  int /*<<< orphan*/  u32 ;
struct stk1160_decimate_ctrl {scalar_t__ col_mode; scalar_t__ row_mode; int /*<<< orphan*/  row_n; int /*<<< orphan*/  col_n; scalar_t__ row_en; scalar_t__ col_en; } ;
struct stk1160 {int dummy; } ;

/* Variables and functions */
 scalar_t__ STK1160_DECIMATE_MORE_THAN_HALF ; 
 int /*<<< orphan*/  STK1160_DEC_UNIT_SIZE ; 
 int /*<<< orphan*/  STK1160_DMCTRL ; 
 int /*<<< orphan*/  STK1160_DMCTRL_H_UNITS ; 
 int /*<<< orphan*/  STK1160_DMCTRL_V_UNITS ; 
 int /*<<< orphan*/  STK1160_H_DEC_EN ; 
 int /*<<< orphan*/  STK1160_H_DEC_MODE ; 
 int /*<<< orphan*/  STK1160_V_DEC_EN ; 
 int /*<<< orphan*/  STK1160_V_DEC_MODE ; 
 int /*<<< orphan*/  stk1160_dbg (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stk1160_write_reg (struct stk1160*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void stk1160_set_fmt(struct stk1160 *dev,
			    struct stk1160_decimate_ctrl *ctrl)
{
	u32 val = 0;

	if (ctrl) {
		/*
		 * Since the format is UYVY, the device must skip or send
		 * a number of rows/columns multiple of four. This way, the
		 * colour format is preserved. The STK1160_DEC_UNIT_SIZE bit
		 * does exactly this.
		 */
		val |= STK1160_DEC_UNIT_SIZE;
		val |= ctrl->col_en ? STK1160_H_DEC_EN : 0;
		val |= ctrl->row_en ? STK1160_V_DEC_EN : 0;
		val |= ctrl->col_mode ==
			STK1160_DECIMATE_MORE_THAN_HALF ?
			STK1160_H_DEC_MODE : 0;
		val |= ctrl->row_mode ==
			STK1160_DECIMATE_MORE_THAN_HALF ?
			STK1160_V_DEC_MODE : 0;

		/* Horizontal count units */
		stk1160_write_reg(dev, STK1160_DMCTRL_H_UNITS, ctrl->col_n);
		/* Vertical count units */
		stk1160_write_reg(dev, STK1160_DMCTRL_V_UNITS, ctrl->row_n);

		stk1160_dbg("decimate 0x%x, column units %d, row units %d\n",
			    val, ctrl->col_n, ctrl->row_n);
	}

	/* Decimation control */
	stk1160_write_reg(dev, STK1160_DMCTRL, val);
}