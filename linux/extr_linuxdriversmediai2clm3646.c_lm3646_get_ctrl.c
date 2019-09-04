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
struct v4l2_ctrl {scalar_t__ id; int /*<<< orphan*/  val; } ;
struct lm3646_flash {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned int FAULT_IVFM ; 
 unsigned int FAULT_NTC_TRIP ; 
 unsigned int FAULT_OCP ; 
 unsigned int FAULT_OVERTEMP ; 
 unsigned int FAULT_OVP ; 
 unsigned int FAULT_SHORT_CIRCUIT ; 
 unsigned int FAULT_TIMEOUT ; 
 unsigned int FAULT_UVLO ; 
 int /*<<< orphan*/  REG_FLAG ; 
 scalar_t__ V4L2_CID_FLASH_FAULT ; 
 int /*<<< orphan*/  V4L2_FLASH_FAULT_INPUT_VOLTAGE ; 
 int /*<<< orphan*/  V4L2_FLASH_FAULT_LED_OVER_TEMPERATURE ; 
 int /*<<< orphan*/  V4L2_FLASH_FAULT_OVER_CURRENT ; 
 int /*<<< orphan*/  V4L2_FLASH_FAULT_OVER_TEMPERATURE ; 
 int /*<<< orphan*/  V4L2_FLASH_FAULT_OVER_VOLTAGE ; 
 int /*<<< orphan*/  V4L2_FLASH_FAULT_SHORT_CIRCUIT ; 
 int /*<<< orphan*/  V4L2_FLASH_FAULT_TIMEOUT ; 
 int /*<<< orphan*/  V4L2_FLASH_FAULT_UNDER_VOLTAGE ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 
 struct lm3646_flash* to_lm3646_flash (struct v4l2_ctrl*) ; 

__attribute__((used)) static int lm3646_get_ctrl(struct v4l2_ctrl *ctrl)
{
	struct lm3646_flash *flash = to_lm3646_flash(ctrl);
	unsigned int reg_val;
	int rval;

	if (ctrl->id != V4L2_CID_FLASH_FAULT)
		return -EINVAL;

	rval = regmap_read(flash->regmap, REG_FLAG, &reg_val);
	if (rval < 0)
		return rval;

	ctrl->val = 0;
	if (reg_val & FAULT_TIMEOUT)
		ctrl->val |= V4L2_FLASH_FAULT_TIMEOUT;
	if (reg_val & FAULT_SHORT_CIRCUIT)
		ctrl->val |= V4L2_FLASH_FAULT_SHORT_CIRCUIT;
	if (reg_val & FAULT_UVLO)
		ctrl->val |= V4L2_FLASH_FAULT_UNDER_VOLTAGE;
	if (reg_val & FAULT_IVFM)
		ctrl->val |= V4L2_FLASH_FAULT_INPUT_VOLTAGE;
	if (reg_val & FAULT_OCP)
		ctrl->val |= V4L2_FLASH_FAULT_OVER_CURRENT;
	if (reg_val & FAULT_OVERTEMP)
		ctrl->val |= V4L2_FLASH_FAULT_OVER_TEMPERATURE;
	if (reg_val & FAULT_NTC_TRIP)
		ctrl->val |= V4L2_FLASH_FAULT_LED_OVER_TEMPERATURE;
	if (reg_val & FAULT_OVP)
		ctrl->val |= V4L2_FLASH_FAULT_OVER_VOLTAGE;

	return 0;
}