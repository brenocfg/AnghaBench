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
typedef  int /*<<< orphan*/  uint32_t ;
struct transform {int /*<<< orphan*/  ctx; } ;

/* Variables and functions */
 int /*<<< orphan*/  COL_MAN_GAMMA_CORR_MEM_PWR_DIS ; 
 int /*<<< orphan*/  COL_MAN_INPUT_GAMMA_MEM_PWR_DIS ; 
 int /*<<< orphan*/  DCFEV_MEM_PWR_CTRL ; 
 int /*<<< orphan*/  dm_read_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dm_write_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ get_reg_field_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmDCFEV_MEM_PWR_CTRL ; 
 int /*<<< orphan*/  set_reg_field_value (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void power_on_lut(struct transform *xfm,
	bool power_on, bool inputgamma, bool regamma)
{
	uint32_t value = dm_read_reg(xfm->ctx, mmDCFEV_MEM_PWR_CTRL);
	int i;

	if (power_on) {
		if (inputgamma)
			set_reg_field_value(
				value,
				1,
				DCFEV_MEM_PWR_CTRL,
				COL_MAN_INPUT_GAMMA_MEM_PWR_DIS);
		if (regamma)
			set_reg_field_value(
				value,
				1,
				DCFEV_MEM_PWR_CTRL,
				COL_MAN_GAMMA_CORR_MEM_PWR_DIS);
	} else {
		if (inputgamma)
			set_reg_field_value(
				value,
				0,
				DCFEV_MEM_PWR_CTRL,
				COL_MAN_INPUT_GAMMA_MEM_PWR_DIS);
		if (regamma)
			set_reg_field_value(
				value,
				0,
				DCFEV_MEM_PWR_CTRL,
				COL_MAN_GAMMA_CORR_MEM_PWR_DIS);
	}

	dm_write_reg(xfm->ctx, mmDCFEV_MEM_PWR_CTRL, value);

	for (i = 0; i < 3; i++) {
		value = dm_read_reg(xfm->ctx, mmDCFEV_MEM_PWR_CTRL);
		if (get_reg_field_value(value,
				DCFEV_MEM_PWR_CTRL,
				COL_MAN_INPUT_GAMMA_MEM_PWR_DIS) &&
			get_reg_field_value(value,
					DCFEV_MEM_PWR_CTRL,
					COL_MAN_GAMMA_CORR_MEM_PWR_DIS))
			break;

		udelay(2);
	}
}