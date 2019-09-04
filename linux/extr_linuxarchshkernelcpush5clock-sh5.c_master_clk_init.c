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
struct clk {int /*<<< orphan*/  rate; } ;

/* Variables and functions */
 int __raw_readl (scalar_t__) ; 
 scalar_t__ cprc_base ; 
 int /*<<< orphan*/ * ifc_table ; 

__attribute__((used)) static void master_clk_init(struct clk *clk)
{
	int idx = (__raw_readl(cprc_base + 0x00) >> 6) & 0x0007;
	clk->rate *= ifc_table[idx];
}