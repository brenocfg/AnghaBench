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
typedef  int u8 ;
struct spmi_regulator_init_data {int pin_ctrl_enable; int pin_ctrl_hpm; int vs_soft_start_strength; } ;
struct spmi_regulator {int logical_type; } ;
typedef  enum spmi_regulator_logical_type { ____Placeholder_spmi_regulator_logical_type } spmi_regulator_logical_type ;

/* Variables and functions */
 int SPMI_COMMON_ENABLE_FOLLOW_ALL_MASK ; 
 size_t SPMI_COMMON_IDX_ENABLE ; 
 size_t SPMI_COMMON_IDX_MODE ; 
 int SPMI_COMMON_MODE_FOLLOW_ALL_MASK ; 
 int SPMI_COMMON_MODE_FOLLOW_AWAKE_MASK ; 
 int /*<<< orphan*/  SPMI_COMMON_REG_VOLTAGE_RANGE ; 
 int SPMI_REGULATOR_LOGICAL_TYPE_LDO ; 
 int SPMI_REGULATOR_LOGICAL_TYPE_SMPS ; 
 int SPMI_REGULATOR_LOGICAL_TYPE_ULT_HO_SMPS ; 
 int SPMI_REGULATOR_LOGICAL_TYPE_ULT_LDO ; 
 int SPMI_REGULATOR_LOGICAL_TYPE_ULT_LO_SMPS ; 
 int SPMI_REGULATOR_LOGICAL_TYPE_VS ; 
 int SPMI_REGULATOR_PIN_CTRL_ENABLE_HW_DEFAULT ; 
 int SPMI_REGULATOR_PIN_CTRL_HPM_HW_DEFAULT ; 
 int /*<<< orphan*/  SPMI_VS_REG_SOFT_START ; 
 int SPMI_VS_SOFT_START_SEL_MASK ; 
 int SPMI_VS_SOFT_START_STR_HW_DEFAULT ; 
 int spmi_vreg_read (struct spmi_regulator*,int /*<<< orphan*/ ,int*,int) ; 
 int spmi_vreg_update_bits (struct spmi_regulator*,int /*<<< orphan*/ ,int,int) ; 
 int spmi_vreg_write (struct spmi_regulator*,int /*<<< orphan*/ ,int*,int) ; 

__attribute__((used)) static int spmi_regulator_init_registers(struct spmi_regulator *vreg,
				const struct spmi_regulator_init_data *data)
{
	int ret;
	enum spmi_regulator_logical_type type;
	u8 ctrl_reg[8], reg, mask;

	type = vreg->logical_type;

	ret = spmi_vreg_read(vreg, SPMI_COMMON_REG_VOLTAGE_RANGE, ctrl_reg, 8);
	if (ret)
		return ret;

	/* Set up enable pin control. */
	if ((type == SPMI_REGULATOR_LOGICAL_TYPE_SMPS
	     || type == SPMI_REGULATOR_LOGICAL_TYPE_LDO
	     || type == SPMI_REGULATOR_LOGICAL_TYPE_VS)
	    && !(data->pin_ctrl_enable
			& SPMI_REGULATOR_PIN_CTRL_ENABLE_HW_DEFAULT)) {
		ctrl_reg[SPMI_COMMON_IDX_ENABLE] &=
			~SPMI_COMMON_ENABLE_FOLLOW_ALL_MASK;
		ctrl_reg[SPMI_COMMON_IDX_ENABLE] |=
		    data->pin_ctrl_enable & SPMI_COMMON_ENABLE_FOLLOW_ALL_MASK;
	}

	/* Set up mode pin control. */
	if ((type == SPMI_REGULATOR_LOGICAL_TYPE_SMPS
	    || type == SPMI_REGULATOR_LOGICAL_TYPE_LDO)
		&& !(data->pin_ctrl_hpm
			& SPMI_REGULATOR_PIN_CTRL_HPM_HW_DEFAULT)) {
		ctrl_reg[SPMI_COMMON_IDX_MODE] &=
			~SPMI_COMMON_MODE_FOLLOW_ALL_MASK;
		ctrl_reg[SPMI_COMMON_IDX_MODE] |=
			data->pin_ctrl_hpm & SPMI_COMMON_MODE_FOLLOW_ALL_MASK;
	}

	if (type == SPMI_REGULATOR_LOGICAL_TYPE_VS
	   && !(data->pin_ctrl_hpm & SPMI_REGULATOR_PIN_CTRL_HPM_HW_DEFAULT)) {
		ctrl_reg[SPMI_COMMON_IDX_MODE] &=
			~SPMI_COMMON_MODE_FOLLOW_AWAKE_MASK;
		ctrl_reg[SPMI_COMMON_IDX_MODE] |=
		       data->pin_ctrl_hpm & SPMI_COMMON_MODE_FOLLOW_AWAKE_MASK;
	}

	if ((type == SPMI_REGULATOR_LOGICAL_TYPE_ULT_LO_SMPS
		|| type == SPMI_REGULATOR_LOGICAL_TYPE_ULT_HO_SMPS
		|| type == SPMI_REGULATOR_LOGICAL_TYPE_ULT_LDO)
		&& !(data->pin_ctrl_hpm
			& SPMI_REGULATOR_PIN_CTRL_HPM_HW_DEFAULT)) {
		ctrl_reg[SPMI_COMMON_IDX_MODE] &=
			~SPMI_COMMON_MODE_FOLLOW_AWAKE_MASK;
		ctrl_reg[SPMI_COMMON_IDX_MODE] |=
		       data->pin_ctrl_hpm & SPMI_COMMON_MODE_FOLLOW_AWAKE_MASK;
	}

	/* Write back any control register values that were modified. */
	ret = spmi_vreg_write(vreg, SPMI_COMMON_REG_VOLTAGE_RANGE, ctrl_reg, 8);
	if (ret)
		return ret;

	/* Set soft start strength and over current protection for VS. */
	if (type == SPMI_REGULATOR_LOGICAL_TYPE_VS) {
		if (data->vs_soft_start_strength
				!= SPMI_VS_SOFT_START_STR_HW_DEFAULT) {
			reg = data->vs_soft_start_strength
				& SPMI_VS_SOFT_START_SEL_MASK;
			mask = SPMI_VS_SOFT_START_SEL_MASK;
			return spmi_vreg_update_bits(vreg,
						     SPMI_VS_REG_SOFT_START,
						     reg, mask);
		}
	}

	return 0;
}