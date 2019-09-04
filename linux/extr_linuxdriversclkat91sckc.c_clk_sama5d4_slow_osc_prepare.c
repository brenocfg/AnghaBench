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
struct clk_sama5d4_slow_osc {int prepared; scalar_t__ startup_usec; int /*<<< orphan*/  sckcr; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int AT91_SCKC_OSCSEL ; 
 int readl (int /*<<< orphan*/ ) ; 
 struct clk_sama5d4_slow_osc* to_clk_sama5d4_slow_osc (struct clk_hw*) ; 
 int /*<<< orphan*/  usleep_range (scalar_t__,scalar_t__) ; 

__attribute__((used)) static int clk_sama5d4_slow_osc_prepare(struct clk_hw *hw)
{
	struct clk_sama5d4_slow_osc *osc = to_clk_sama5d4_slow_osc(hw);

	if (osc->prepared)
		return 0;

	/*
	 * Assume that if it has already been selected (for example by the
	 * bootloader), enough time has aready passed.
	 */
	if ((readl(osc->sckcr) & AT91_SCKC_OSCSEL)) {
		osc->prepared = true;
		return 0;
	}

	usleep_range(osc->startup_usec, osc->startup_usec + 1);
	osc->prepared = true;

	return 0;
}