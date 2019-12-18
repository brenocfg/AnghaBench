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

/* Variables and functions */
 int /*<<< orphan*/  POWER_MODE_CTRL ; 
 unsigned int POWER_MODE_CTRL_336CLK ; 
 unsigned int POWER_MODE_CTRL_MODE_MASK ; 
#define  POWER_MODE_CTRL_MODE_MODE0 130 
#define  POWER_MODE_CTRL_MODE_MODE1 129 
#define  POWER_MODE_CTRL_MODE_SLEEP 128 
 unsigned int POWER_MODE_CTRL_OSC_INPUT ; 
 scalar_t__ SM750LE ; 
 unsigned int peek32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  poke32 (int /*<<< orphan*/ ,unsigned int) ; 
 scalar_t__ sm750_get_chip_type () ; 

void sm750_set_power_mode(unsigned int mode)
{
	unsigned int ctrl = 0;

	ctrl = peek32(POWER_MODE_CTRL) & ~POWER_MODE_CTRL_MODE_MASK;

	if (sm750_get_chip_type() == SM750LE)
		return;

	switch (mode) {
	case POWER_MODE_CTRL_MODE_MODE0:
		ctrl |= POWER_MODE_CTRL_MODE_MODE0;
		break;

	case POWER_MODE_CTRL_MODE_MODE1:
		ctrl |= POWER_MODE_CTRL_MODE_MODE1;
		break;

	case POWER_MODE_CTRL_MODE_SLEEP:
		ctrl |= POWER_MODE_CTRL_MODE_SLEEP;
		break;

	default:
		break;
	}

	/* Set up other fields in Power Control Register */
	if (mode == POWER_MODE_CTRL_MODE_SLEEP) {
		ctrl &= ~POWER_MODE_CTRL_OSC_INPUT;
#ifdef VALIDATION_CHIP
		ctrl &= ~POWER_MODE_CTRL_336CLK;
#endif
	} else {
		ctrl |= POWER_MODE_CTRL_OSC_INPUT;
#ifdef VALIDATION_CHIP
		ctrl |= POWER_MODE_CTRL_336CLK;
#endif
	}

	/* Program new power mode. */
	poke32(POWER_MODE_CTRL, ctrl);
}