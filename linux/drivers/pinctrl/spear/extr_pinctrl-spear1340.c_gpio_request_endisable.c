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
struct spear_pmx {int dummy; } ;

/* Variables and functions */
 unsigned int PAD_FUNCTION_EN_1 ; 
 unsigned int PAD_FUNCTION_EN_5 ; 
 unsigned int pmx_readl (struct spear_pmx*,unsigned int) ; 
 int /*<<< orphan*/  pmx_writel (struct spear_pmx*,unsigned int,unsigned int) ; 

__attribute__((used)) static void gpio_request_endisable(struct spear_pmx *pmx, int pin,
		bool enable)
{
	unsigned int regoffset, regindex, bitoffset;
	unsigned int val;

	/* pin++ as gpio configuration starts from 2nd bit of base register */
	pin++;

	regindex = pin / 32;
	bitoffset = pin % 32;

	if (regindex <= 3)
		regoffset = PAD_FUNCTION_EN_1 + regindex * sizeof(int *);
	else
		regoffset = PAD_FUNCTION_EN_5 + (regindex - 4) * sizeof(int *);

	val = pmx_readl(pmx, regoffset);
	if (enable)
		val &= ~(0x1 << bitoffset);
	else
		val |= 0x1 << bitoffset;

	pmx_writel(pmx, val, regoffset);
}