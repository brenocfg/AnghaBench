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
struct TYPE_2__ {int div_mask; int div_shift; } ;

/* Variables and functions */
 int /*<<< orphan*/  PRCMU_TVCLK ; 
 int /*<<< orphan*/  PRCM_DSITVCLK_DIV ; 
 int clock_divider (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  clock_rate (int /*<<< orphan*/ ) ; 
 TYPE_1__* dsiescclk ; 
 int min (int,int) ; 
 int readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void set_dsiescclk_rate(u8 n, unsigned long rate)
{
	u32 val;
	u32 div;

	div = clock_divider(clock_rate(PRCMU_TVCLK), rate);
	val = readl(PRCM_DSITVCLK_DIV);
	val &= ~dsiescclk[n].div_mask;
	val |= (min(div, (u32)255) << dsiescclk[n].div_shift);
	writel(val, PRCM_DSITVCLK_DIV);
}