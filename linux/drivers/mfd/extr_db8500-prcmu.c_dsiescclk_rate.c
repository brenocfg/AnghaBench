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
 unsigned long clock_rate (int /*<<< orphan*/ ) ; 
 TYPE_1__* dsiescclk ; 
 unsigned long max (int,int) ; 
 int readl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned long dsiescclk_rate(u8 n)
{
	u32 div;

	div = readl(PRCM_DSITVCLK_DIV);
	div = ((div & dsiescclk[n].div_mask) >> (dsiescclk[n].div_shift));
	return clock_rate(PRCMU_TVCLK) / max((u32)1, div);
}