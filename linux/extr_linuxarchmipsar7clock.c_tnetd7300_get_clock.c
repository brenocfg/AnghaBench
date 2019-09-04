#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct tnetd7300_clock {int /*<<< orphan*/  pll; int /*<<< orphan*/  ctrl; } ;
struct TYPE_2__ {int rate; } ;

/* Variables and functions */
 int AR7_REF_CLOCK ; 
 int AR7_XTAL_CLOCK ; 
 int BOOT_PLL_BYPASS ; 
#define  BOOT_PLL_SOURCE_BUS 131 
#define  BOOT_PLL_SOURCE_CPU 130 
 int BOOT_PLL_SOURCE_MASK ; 
#define  BOOT_PLL_SOURCE_REF 129 
#define  BOOT_PLL_SOURCE_XTAL 128 
 int MUL_MASK ; 
 int MUL_SHIFT ; 
 int PLL_DIV ; 
 int PLL_MODE_MASK ; 
 int PLL_NDIV ; 
 int POSTDIV_MASK ; 
 int PREDIV_MASK ; 
 int PREDIV_SHIFT ; 
 TYPE_1__ cpu_clk ; 
 int readl (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int tnetd7300_get_clock(u32 shift, struct tnetd7300_clock *clock,
	u32 *bootcr, u32 bus_clock)
{
	int product;
	int base_clock = AR7_REF_CLOCK;
	u32 ctrl = readl(&clock->ctrl);
	u32 pll = readl(&clock->pll);
	int prediv = ((ctrl & PREDIV_MASK) >> PREDIV_SHIFT) + 1;
	int postdiv = (ctrl & POSTDIV_MASK) + 1;
	int divisor = prediv * postdiv;
	int mul = ((pll & MUL_MASK) >> MUL_SHIFT) + 1;

	switch ((*bootcr & (BOOT_PLL_SOURCE_MASK << shift)) >> shift) {
	case BOOT_PLL_SOURCE_BUS:
		base_clock = bus_clock;
		break;
	case BOOT_PLL_SOURCE_REF:
		base_clock = AR7_REF_CLOCK;
		break;
	case BOOT_PLL_SOURCE_XTAL:
		base_clock = AR7_XTAL_CLOCK;
		break;
	case BOOT_PLL_SOURCE_CPU:
		base_clock = cpu_clk.rate;
		break;
	}

	if (*bootcr & BOOT_PLL_BYPASS)
		return base_clock / divisor;

	if ((pll & PLL_MODE_MASK) == 0)
		return (base_clock >> (mul / 16 + 1)) / divisor;

	if ((pll & (PLL_NDIV | PLL_DIV)) == (PLL_NDIV | PLL_DIV)) {
		product = (mul & 1) ?
			(base_clock * mul) >> 1 :
			(base_clock * (mul - 1)) >> 2;
		return product / divisor;
	}

	if (mul == 16)
		return base_clock / divisor;

	return base_clock * mul / divisor;
}