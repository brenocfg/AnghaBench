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
struct fusb302_chip {int intr_bc_lvl; int intr_comp_chng; int intr_togdone; int toggling_mode; void* cc2; void* cc1; int /*<<< orphan*/  vconn_on; } ;
typedef  enum toggling_mode { ____Placeholder_toggling_mode } toggling_mode ;

/* Variables and functions */
 int /*<<< orphan*/  FUSB_REG_CONTROL2 ; 
 int /*<<< orphan*/  FUSB_REG_CONTROL2_MODE_DFP ; 
 int /*<<< orphan*/  FUSB_REG_CONTROL2_MODE_DRP ; 
 int /*<<< orphan*/  FUSB_REG_CONTROL2_MODE_MASK ; 
 int /*<<< orphan*/  FUSB_REG_CONTROL2_MODE_NONE ; 
 int /*<<< orphan*/  FUSB_REG_CONTROL2_MODE_UFP ; 
 int FUSB_REG_CONTROL2_TOGGLE ; 
 int /*<<< orphan*/  FUSB_REG_MASK ; 
 int /*<<< orphan*/  FUSB_REG_MASKA ; 
 int FUSB_REG_MASKA_TOGDONE ; 
 int FUSB_REG_MASK_BC_LVL ; 
 int FUSB_REG_MASK_COMP_CHNG ; 
#define  TOGGLING_MODE_DRP 131 
#define  TOGGLING_MODE_OFF 130 
#define  TOGGLING_MODE_SNK 129 
#define  TOGGLING_MODE_SRC 128 
 void* TYPEC_CC_OPEN ; 
 int /*<<< orphan*/  WARN (int /*<<< orphan*/ ,char*) ; 
 int fusb302_i2c_clear_bits (struct fusb302_chip*,int /*<<< orphan*/ ,int) ; 
 int fusb302_i2c_mask_write (struct fusb302_chip*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int fusb302_i2c_set_bits (struct fusb302_chip*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int fusb302_set_toggling(struct fusb302_chip *chip,
				enum toggling_mode mode)
{
	int ret = 0;

	/* first disable toggling */
	ret = fusb302_i2c_clear_bits(chip, FUSB_REG_CONTROL2,
				     FUSB_REG_CONTROL2_TOGGLE);
	if (ret < 0)
		return ret;
	/* mask interrupts for SRC or SNK */
	ret = fusb302_i2c_set_bits(chip, FUSB_REG_MASK,
				   FUSB_REG_MASK_BC_LVL |
				   FUSB_REG_MASK_COMP_CHNG);
	if (ret < 0)
		return ret;
	chip->intr_bc_lvl = false;
	chip->intr_comp_chng = false;
	/* configure toggling mode: none/snk/src/drp */
	switch (mode) {
	case TOGGLING_MODE_OFF:
		ret = fusb302_i2c_mask_write(chip, FUSB_REG_CONTROL2,
					     FUSB_REG_CONTROL2_MODE_MASK,
					     FUSB_REG_CONTROL2_MODE_NONE);
		if (ret < 0)
			return ret;
		break;
	case TOGGLING_MODE_SNK:
		ret = fusb302_i2c_mask_write(chip, FUSB_REG_CONTROL2,
					     FUSB_REG_CONTROL2_MODE_MASK,
					     FUSB_REG_CONTROL2_MODE_UFP);
		if (ret < 0)
			return ret;
		break;
	case TOGGLING_MODE_SRC:
		ret = fusb302_i2c_mask_write(chip, FUSB_REG_CONTROL2,
					     FUSB_REG_CONTROL2_MODE_MASK,
					     FUSB_REG_CONTROL2_MODE_DFP);
		if (ret < 0)
			return ret;
		break;
	case TOGGLING_MODE_DRP:
		ret = fusb302_i2c_mask_write(chip, FUSB_REG_CONTROL2,
					     FUSB_REG_CONTROL2_MODE_MASK,
					     FUSB_REG_CONTROL2_MODE_DRP);
		if (ret < 0)
			return ret;
		break;
	default:
		break;
	}

	if (mode == TOGGLING_MODE_OFF) {
		/* mask TOGDONE interrupt */
		ret = fusb302_i2c_set_bits(chip, FUSB_REG_MASKA,
					   FUSB_REG_MASKA_TOGDONE);
		if (ret < 0)
			return ret;
		chip->intr_togdone = false;
	} else {
		/* Datasheet says vconn MUST be off when toggling */
		WARN(chip->vconn_on, "Vconn is on during toggle start");
		/* unmask TOGDONE interrupt */
		ret = fusb302_i2c_clear_bits(chip, FUSB_REG_MASKA,
					     FUSB_REG_MASKA_TOGDONE);
		if (ret < 0)
			return ret;
		chip->intr_togdone = true;
		/* start toggling */
		ret = fusb302_i2c_set_bits(chip, FUSB_REG_CONTROL2,
					   FUSB_REG_CONTROL2_TOGGLE);
		if (ret < 0)
			return ret;
		/* during toggling, consider cc as Open */
		chip->cc1 = TYPEC_CC_OPEN;
		chip->cc2 = TYPEC_CC_OPEN;
	}
	chip->toggling_mode = mode;

	return ret;
}