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
struct v4l2_ctrl {int id; int val; } ;
struct lm3646_flash {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int EINVAL ; 
 int LM3646_FLASH_TOUT_ms_TO_REG (int) ; 
 int LM3646_TOTAL_FLASH_BRT_uA_TO_REG (int) ; 
 int LM3646_TOTAL_TORCH_BRT_uA_TO_REG (int) ; 
 unsigned int MASK_ENABLE ; 
 int /*<<< orphan*/  MASK_FLASH_BR ; 
 int /*<<< orphan*/  MASK_FLASH_TOUT ; 
 int /*<<< orphan*/  MASK_STROBE_SRC ; 
 int /*<<< orphan*/  MASK_TORCH_BR ; 
 unsigned int MODE_FLASH ; 
 unsigned int MODE_SHDN ; 
 int /*<<< orphan*/  REG_ENABLE ; 
 int /*<<< orphan*/  REG_FLASH_BR ; 
 int /*<<< orphan*/  REG_FLASH_TOUT ; 
 int /*<<< orphan*/  REG_STROBE_SRC ; 
 int /*<<< orphan*/  REG_TORCH_BR ; 
#define  V4L2_CID_FLASH_INTENSITY 134 
#define  V4L2_CID_FLASH_LED_MODE 133 
#define  V4L2_CID_FLASH_STROBE 132 
#define  V4L2_CID_FLASH_STROBE_SOURCE 131 
#define  V4L2_CID_FLASH_STROBE_STOP 130 
#define  V4L2_CID_FLASH_TIMEOUT 129 
#define  V4L2_CID_FLASH_TORCH_INTENSITY 128 
 int V4L2_FLASH_LED_MODE_FLASH ; 
 int V4L2_FLASH_LED_MODE_NONE ; 
 int lm3646_mode_ctrl (struct lm3646_flash*,int) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct lm3646_flash* to_lm3646_flash (struct v4l2_ctrl*) ; 

__attribute__((used)) static int lm3646_set_ctrl(struct v4l2_ctrl *ctrl)
{
	struct lm3646_flash *flash = to_lm3646_flash(ctrl);
	unsigned int reg_val;
	int rval = -EINVAL;

	switch (ctrl->id) {
	case V4L2_CID_FLASH_LED_MODE:

		if (ctrl->val != V4L2_FLASH_LED_MODE_FLASH)
			return lm3646_mode_ctrl(flash, ctrl->val);
		/* switch to SHDN mode before flash strobe on */
		return lm3646_mode_ctrl(flash, V4L2_FLASH_LED_MODE_NONE);

	case V4L2_CID_FLASH_STROBE_SOURCE:
		return regmap_update_bits(flash->regmap,
					  REG_STROBE_SRC, MASK_STROBE_SRC,
					  (ctrl->val) << 7);

	case V4L2_CID_FLASH_STROBE:

		/* read and check current mode of chip to start flash */
		rval = regmap_read(flash->regmap, REG_ENABLE, &reg_val);
		if (rval < 0 || ((reg_val & MASK_ENABLE) != MODE_SHDN))
			return rval;
		/* flash on */
		return lm3646_mode_ctrl(flash, V4L2_FLASH_LED_MODE_FLASH);

	case V4L2_CID_FLASH_STROBE_STOP:

		/*
		 * flash mode will be turned automatically
		 * from FLASH mode to SHDN mode after flash duration timeout
		 * read and check current mode of chip to stop flash
		 */
		rval = regmap_read(flash->regmap, REG_ENABLE, &reg_val);
		if (rval < 0)
			return rval;
		if ((reg_val & MASK_ENABLE) == MODE_FLASH)
			return lm3646_mode_ctrl(flash,
						V4L2_FLASH_LED_MODE_NONE);
		return rval;

	case V4L2_CID_FLASH_TIMEOUT:
		return regmap_update_bits(flash->regmap,
					  REG_FLASH_TOUT, MASK_FLASH_TOUT,
					  LM3646_FLASH_TOUT_ms_TO_REG
					  (ctrl->val));

	case V4L2_CID_FLASH_INTENSITY:
		return regmap_update_bits(flash->regmap,
					  REG_FLASH_BR, MASK_FLASH_BR,
					  LM3646_TOTAL_FLASH_BRT_uA_TO_REG
					  (ctrl->val));

	case V4L2_CID_FLASH_TORCH_INTENSITY:
		return regmap_update_bits(flash->regmap,
					  REG_TORCH_BR, MASK_TORCH_BR,
					  LM3646_TOTAL_TORCH_BRT_uA_TO_REG
					  (ctrl->val) << 4);
	}

	return -EINVAL;
}