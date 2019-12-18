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
typedef  scalar_t__ uint32_t ;
struct dce_aux {int dummy; } ;
struct aux_engine_dce110 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUX_ARB_CONTROL ; 
 int /*<<< orphan*/  AUX_CONTROL ; 
 int /*<<< orphan*/  AUX_EN ; 
 int /*<<< orphan*/  AUX_REG_RW_CNTL_STATUS ; 
 int /*<<< orphan*/  AUX_RESET ; 
 int /*<<< orphan*/  AUX_RESET_DONE ; 
 int /*<<< orphan*/  AUX_RESET_MASK ; 
 int /*<<< orphan*/  AUX_SW_USE_AUX_REG_REQ ; 
 scalar_t__ DMCU_CAN_ACCESS_AUX ; 
 struct aux_engine_dce110* FROM_AUX_ENGINE (struct dce_aux*) ; 
 scalar_t__ REG (int /*<<< orphan*/ ) ; 
 scalar_t__ REG_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_UPDATE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  REG_WAIT (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  REG_WRITE (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ SW_CAN_ACCESS_AUX ; 
 scalar_t__ get_reg_field_value (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_reg_field_value (scalar_t__,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool acquire_engine(
	struct dce_aux *engine)
{
	struct aux_engine_dce110 *aux110 = FROM_AUX_ENGINE(engine);

	uint32_t value = REG_READ(AUX_ARB_CONTROL);
	uint32_t field = get_reg_field_value(
			value,
			AUX_ARB_CONTROL,
			AUX_REG_RW_CNTL_STATUS);
	if (field == DMCU_CAN_ACCESS_AUX)
		return false;
	/* enable AUX before request SW to access AUX */
	value = REG_READ(AUX_CONTROL);
	field = get_reg_field_value(value,
				AUX_CONTROL,
				AUX_EN);

	if (field == 0) {
		set_reg_field_value(
				value,
				1,
				AUX_CONTROL,
				AUX_EN);

		if (REG(AUX_RESET_MASK)) {
			/*DP_AUX block as part of the enable sequence*/
			set_reg_field_value(
				value,
				1,
				AUX_CONTROL,
				AUX_RESET);
		}

		REG_WRITE(AUX_CONTROL, value);

		if (REG(AUX_RESET_MASK)) {
			/*poll HW to make sure reset it done*/

			REG_WAIT(AUX_CONTROL, AUX_RESET_DONE, 1,
					1, 11);

			set_reg_field_value(
				value,
				0,
				AUX_CONTROL,
				AUX_RESET);

			REG_WRITE(AUX_CONTROL, value);

			REG_WAIT(AUX_CONTROL, AUX_RESET_DONE, 0,
					1, 11);
		}
	} /*if (field)*/

	/* request SW to access AUX */
	REG_UPDATE(AUX_ARB_CONTROL, AUX_SW_USE_AUX_REG_REQ, 1);

	value = REG_READ(AUX_ARB_CONTROL);
	field = get_reg_field_value(
			value,
			AUX_ARB_CONTROL,
			AUX_REG_RW_CNTL_STATUS);

	return (field == SW_CAN_ACCESS_AUX);
}