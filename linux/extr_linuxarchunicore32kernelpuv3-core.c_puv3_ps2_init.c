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
struct clk {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PS2_CNT ; 
 struct clk* clk_get (int /*<<< orphan*/ *,char*) ; 
 int clk_get_rate (struct clk*) ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ ) ; 

void puv3_ps2_init(void)
{
	struct clk *bclk32;

	bclk32 = clk_get(NULL, "BUS32_CLK");
	writel(clk_get_rate(bclk32) / 200000, PS2_CNT); /* should > 5us */
}