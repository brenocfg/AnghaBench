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
struct fusb302_chip {int src_current_status; } ;
typedef  enum src_current_status { ____Placeholder_src_current_status } src_current_status ;

/* Variables and functions */
 int /*<<< orphan*/  FUSB_REG_CONTROL0 ; 
 int /*<<< orphan*/  FUSB_REG_CONTROL0_HOST_CUR_DEF ; 
 int /*<<< orphan*/  FUSB_REG_CONTROL0_HOST_CUR_HIGH ; 
 int /*<<< orphan*/  FUSB_REG_CONTROL0_HOST_CUR_MASK ; 
 int /*<<< orphan*/  FUSB_REG_CONTROL0_HOST_CUR_MED ; 
#define  SRC_CURRENT_DEFAULT 130 
#define  SRC_CURRENT_HIGH 129 
#define  SRC_CURRENT_MEDIUM 128 
 int fusb302_i2c_mask_write (struct fusb302_chip*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int fusb302_set_src_current(struct fusb302_chip *chip,
				   enum src_current_status status)
{
	int ret = 0;

	chip->src_current_status = status;
	switch (status) {
	case SRC_CURRENT_DEFAULT:
		ret = fusb302_i2c_mask_write(chip, FUSB_REG_CONTROL0,
					     FUSB_REG_CONTROL0_HOST_CUR_MASK,
					     FUSB_REG_CONTROL0_HOST_CUR_DEF);
		break;
	case SRC_CURRENT_MEDIUM:
		ret = fusb302_i2c_mask_write(chip, FUSB_REG_CONTROL0,
					     FUSB_REG_CONTROL0_HOST_CUR_MASK,
					     FUSB_REG_CONTROL0_HOST_CUR_MED);
		break;
	case SRC_CURRENT_HIGH:
		ret = fusb302_i2c_mask_write(chip, FUSB_REG_CONTROL0,
					     FUSB_REG_CONTROL0_HOST_CUR_MASK,
					     FUSB_REG_CONTROL0_HOST_CUR_HIGH);
		break;
	default:
		break;
	}

	return ret;
}