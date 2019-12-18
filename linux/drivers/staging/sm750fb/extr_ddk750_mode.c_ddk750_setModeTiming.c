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
struct pll_value {int clockType; int /*<<< orphan*/  inputFreq; } ;
struct mode_parameter {int /*<<< orphan*/  pixel_clock; } ;
typedef  enum clock_type { ____Placeholder_clock_type } clock_type ;

/* Variables and functions */
 int /*<<< orphan*/  DEFAULT_INPUT_CLOCK ; 
 scalar_t__ SM750LE ; 
 int /*<<< orphan*/  outb_p (int,int) ; 
 int /*<<< orphan*/  programModeRegisters (struct mode_parameter*,struct pll_value*) ; 
 unsigned int sm750_calc_pll_value (int /*<<< orphan*/ ,struct pll_value*) ; 
 scalar_t__ sm750_get_chip_type () ; 

int ddk750_setModeTiming(struct mode_parameter *parm, enum clock_type clock)
{
	struct pll_value pll;
	unsigned int uiActualPixelClk;

	pll.inputFreq = DEFAULT_INPUT_CLOCK;
	pll.clockType = clock;

	uiActualPixelClk = sm750_calc_pll_value(parm->pixel_clock, &pll);
	if (sm750_get_chip_type() == SM750LE) {
		/* set graphic mode via IO method */
		outb_p(0x88, 0x3d4);
		outb_p(0x06, 0x3d5);
	}
	programModeRegisters(parm, &pll);
	return 0;
}