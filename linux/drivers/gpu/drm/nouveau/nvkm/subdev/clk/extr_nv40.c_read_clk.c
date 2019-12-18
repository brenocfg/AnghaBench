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
typedef  int u32 ;
struct nv40_clk {int dummy; } ;

/* Variables and functions */
 int read_pll_1 (struct nv40_clk*,int) ; 
 int read_pll_2 (struct nv40_clk*,int) ; 

__attribute__((used)) static u32
read_clk(struct nv40_clk *clk, u32 src)
{
	switch (src) {
	case 3:
		return read_pll_2(clk, 0x004000);
	case 2:
		return read_pll_1(clk, 0x004008);
	default:
		break;
	}

	return 0;
}