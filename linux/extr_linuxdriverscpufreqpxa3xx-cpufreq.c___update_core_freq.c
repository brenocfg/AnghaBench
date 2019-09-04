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
typedef  int uint32_t ;
struct pxa3xx_freq_info {int core_xn; int /*<<< orphan*/  core_xl; } ;

/* Variables and functions */
 int ACCR ; 
 int ACCR_XL (int /*<<< orphan*/ ) ; 
 int ACCR_XL_MASK ; 
 int ACCR_XN (int) ; 
 int ACCR_XN_MASK ; 
 int ACCR_XSPCLK (int /*<<< orphan*/ ) ; 
 int ACCR_XSPCLK_MASK ; 
 int ACSR ; 
 int /*<<< orphan*/  XSPCLK_NONE ; 
 int /*<<< orphan*/  cpu_relax () ; 

__attribute__((used)) static void __update_core_freq(struct pxa3xx_freq_info *info)
{
	uint32_t mask = ACCR_XN_MASK | ACCR_XL_MASK;
	uint32_t accr = ACCR;
	uint32_t xclkcfg;

	accr &= ~(ACCR_XN_MASK | ACCR_XL_MASK | ACCR_XSPCLK_MASK);
	accr |= ACCR_XN(info->core_xn) | ACCR_XL(info->core_xl);

	/* No clock until core PLL is re-locked */
	accr |= ACCR_XSPCLK(XSPCLK_NONE);

	xclkcfg = (info->core_xn == 2) ? 0x3 : 0x2;	/* turbo bit */

	ACCR = accr;
	__asm__("mcr p14, 0, %0, c6, c0, 0\n" : : "r"(xclkcfg));

	while ((ACSR & mask) != (accr & mask))
		cpu_relax();
}