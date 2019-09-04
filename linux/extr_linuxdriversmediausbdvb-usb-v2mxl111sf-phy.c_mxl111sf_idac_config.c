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
typedef  scalar_t__ u8 ;
struct mxl111sf_state {int dummy; } ;

/* Variables and functions */
 scalar_t__ IDAC_CURRENT_SINKING_BIT_MASK ; 
 scalar_t__ IDAC_CURRENT_SINKING_ENABLE ; 
 scalar_t__ IDAC_MANUAL_CONTROL ; 
 scalar_t__ IDAC_MANUAL_CONTROL_BIT_MASK ; 
 int /*<<< orphan*/  V6_IDAC_HYSTERESIS_REG ; 
 int /*<<< orphan*/  V6_IDAC_SETTINGS_REG ; 
 int mxl111sf_write_reg (struct mxl111sf_state*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  mxl_fail (int) ; 

int mxl111sf_idac_config(struct mxl111sf_state *state,
			 u8 control_mode, u8 current_setting,
			 u8 current_value, u8 hysteresis_value)
{
	int ret;
	u8 val;
	/* current value will be set for both automatic & manual IDAC control */
	val = current_value;

	if (control_mode == IDAC_MANUAL_CONTROL) {
		/* enable manual control of IDAC */
		val |= IDAC_MANUAL_CONTROL_BIT_MASK;

		if (current_setting == IDAC_CURRENT_SINKING_ENABLE)
			/* enable current sinking in manual mode */
			val |= IDAC_CURRENT_SINKING_BIT_MASK;
		else
			/* disable current sinking in manual mode */
			val &= ~IDAC_CURRENT_SINKING_BIT_MASK;
	} else {
		/* disable manual control of IDAC */
		val &= ~IDAC_MANUAL_CONTROL_BIT_MASK;

		/* set hysteresis value  reg: 0x0B<5:0> */
		ret = mxl111sf_write_reg(state, V6_IDAC_HYSTERESIS_REG,
					 (hysteresis_value & 0x3F));
		mxl_fail(ret);
	}

	ret = mxl111sf_write_reg(state, V6_IDAC_SETTINGS_REG, val);
	mxl_fail(ret);

	return ret;
}