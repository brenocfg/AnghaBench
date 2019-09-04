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
typedef  size_t u8 ;
typedef  int u32 ;
struct TYPE_2__ {int divsel; int divsel_mask; int divsel_shift; } ;

/* Variables and functions */
 int /*<<< orphan*/  PLL_RAW ; 
 int /*<<< orphan*/  PRCMU_HDMICLK ; 
 int /*<<< orphan*/  PRCM_DSI_PLLOUT_SEL ; 
 int PRCM_DSI_PLLOUT_SEL_PHI ; 
 int PRCM_DSI_PLLOUT_SEL_PHI_2 ; 
 int PRCM_DSI_PLLOUT_SEL_PHI_4 ; 
 int /*<<< orphan*/  PRCM_PLLDSI_FREQ ; 
 int clock_divider (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  clock_rate (int /*<<< orphan*/ ) ; 
 TYPE_1__* dsiclk ; 
 int /*<<< orphan*/  pll_rate (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void set_dsiclk_rate(u8 n, unsigned long rate)
{
	u32 val;
	u32 div;

	div = clock_divider(pll_rate(PRCM_PLLDSI_FREQ,
			clock_rate(PRCMU_HDMICLK), PLL_RAW), rate);

	dsiclk[n].divsel = (div == 1) ? PRCM_DSI_PLLOUT_SEL_PHI :
			   (div == 2) ? PRCM_DSI_PLLOUT_SEL_PHI_2 :
			   /* else */	PRCM_DSI_PLLOUT_SEL_PHI_4;

	val = readl(PRCM_DSI_PLLOUT_SEL);
	val &= ~dsiclk[n].divsel_mask;
	val |= (dsiclk[n].divsel << dsiclk[n].divsel_shift);
	writel(val, PRCM_DSI_PLLOUT_SEL);
}