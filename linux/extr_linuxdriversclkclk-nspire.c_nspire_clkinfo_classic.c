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
struct nspire_clk_info {int base_clock; int base_cpu_ratio; int base_ahb_ratio; } ;

/* Variables and functions */
 int /*<<< orphan*/  BASE_CPU ; 
 int /*<<< orphan*/  CLASSIC_BASE ; 
 int /*<<< orphan*/  CPU_AHB ; 
 int EXTRACT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FIXED_BASE ; 
 int MHZ ; 

__attribute__((used)) static void nspire_clkinfo_classic(u32 val, struct nspire_clk_info *clk)
{
	if (EXTRACT(val, FIXED_BASE))
		clk->base_clock = 27 * MHZ;
	else
		clk->base_clock = (300 - 6 * EXTRACT(val, CLASSIC_BASE)) * MHZ;

	clk->base_cpu_ratio = EXTRACT(val, BASE_CPU) * 2;
	clk->base_ahb_ratio = clk->base_cpu_ratio * (EXTRACT(val, CPU_AHB) + 1);
}