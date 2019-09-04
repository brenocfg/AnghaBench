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
struct macb {int /*<<< orphan*/  pclk; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLK ; 
 int /*<<< orphan*/  GEM_BF (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GEM_CLK_DIV16 ; 
 int /*<<< orphan*/  GEM_CLK_DIV32 ; 
 int /*<<< orphan*/  GEM_CLK_DIV48 ; 
 int /*<<< orphan*/  GEM_CLK_DIV64 ; 
 int /*<<< orphan*/  GEM_CLK_DIV8 ; 
 int /*<<< orphan*/  GEM_CLK_DIV96 ; 
 unsigned long clk_get_rate (int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 gem_mdc_clk_div(struct macb *bp)
{
	u32 config;
	unsigned long pclk_hz = clk_get_rate(bp->pclk);

	if (pclk_hz <= 20000000)
		config = GEM_BF(CLK, GEM_CLK_DIV8);
	else if (pclk_hz <= 40000000)
		config = GEM_BF(CLK, GEM_CLK_DIV16);
	else if (pclk_hz <= 80000000)
		config = GEM_BF(CLK, GEM_CLK_DIV32);
	else if (pclk_hz <= 120000000)
		config = GEM_BF(CLK, GEM_CLK_DIV48);
	else if (pclk_hz <= 160000000)
		config = GEM_BF(CLK, GEM_CLK_DIV64);
	else
		config = GEM_BF(CLK, GEM_CLK_DIV96);

	return config;
}