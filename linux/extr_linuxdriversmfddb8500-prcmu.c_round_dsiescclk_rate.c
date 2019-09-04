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
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 int /*<<< orphan*/  PRCMU_TVCLK ; 
 int /*<<< orphan*/  clock_divider (unsigned long,unsigned long) ; 
 unsigned long clock_rate (int /*<<< orphan*/ ) ; 
 unsigned long min (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static long round_dsiescclk_rate(unsigned long rate)
{
	u32 div;
	unsigned long src_rate;
	long rounded_rate;

	src_rate = clock_rate(PRCMU_TVCLK);
	div = clock_divider(src_rate, rate);
	rounded_rate = (src_rate / min(div, (u32)255));

	return rounded_rate;
}