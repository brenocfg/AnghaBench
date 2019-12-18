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
struct atyfb_par {int dummy; } ;

/* Variables and functions */
 scalar_t__ DAC_REGS ; 
 int /*<<< orphan*/  aty_ld_8 (scalar_t__,struct atyfb_par const*) ; 

__attribute__((used)) static void aty_dac_waste4(const struct atyfb_par *par)
{
	(void) aty_ld_8(DAC_REGS, par);

	(void) aty_ld_8(DAC_REGS + 2, par);
	(void) aty_ld_8(DAC_REGS + 2, par);
	(void) aty_ld_8(DAC_REGS + 2, par);
	(void) aty_ld_8(DAC_REGS + 2, par);
}