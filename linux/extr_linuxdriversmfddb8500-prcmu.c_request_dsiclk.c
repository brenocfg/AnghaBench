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
struct TYPE_2__ {int divsel_mask; int divsel; int divsel_shift; } ;

/* Variables and functions */
 int /*<<< orphan*/  PRCM_DSI_PLLOUT_SEL ; 
 int PRCM_DSI_PLLOUT_SEL_OFF ; 
 TYPE_1__* dsiclk ; 
 int readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int request_dsiclk(u8 n, bool enable)
{
	u32 val;

	val = readl(PRCM_DSI_PLLOUT_SEL);
	val &= ~dsiclk[n].divsel_mask;
	val |= ((enable ? dsiclk[n].divsel : PRCM_DSI_PLLOUT_SEL_OFF) <<
		dsiclk[n].divsel_shift);
	writel(val, PRCM_DSI_PLLOUT_SEL);
	return 0;
}