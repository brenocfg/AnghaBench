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
typedef  unsigned long long uint64_t ;
struct TYPE_2__ {unsigned long long sysbase; } ;

/* Variables and functions */
 int /*<<< orphan*/  SYS_CORE_DFS_DIV_VALUE ; 
 int /*<<< orphan*/  SYS_POWER_ON_RESET_CFG ; 
 int /*<<< orphan*/  do_div (unsigned long long,unsigned int) ; 
 TYPE_1__* nlm_get_node (int) ; 
 unsigned int nlm_read_sys_reg (unsigned long long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned int nlm_xlp_get_core_frequency(int node, int core)
{
	unsigned int pll_divf, pll_divr, dfs_div, ext_div;
	unsigned int rstval, dfsval, denom;
	uint64_t num, sysbase;

	sysbase = nlm_get_node(node)->sysbase;
	rstval = nlm_read_sys_reg(sysbase, SYS_POWER_ON_RESET_CFG);
	dfsval = nlm_read_sys_reg(sysbase, SYS_CORE_DFS_DIV_VALUE);
	pll_divf = ((rstval >> 10) & 0x7f) + 1;
	pll_divr = ((rstval >> 8)  & 0x3) + 1;
	ext_div  = ((rstval >> 30) & 0x3) + 1;
	dfs_div  = ((dfsval >> (core * 4)) & 0xf) + 1;

	num = 800000000ULL * pll_divf;
	denom = 3 * pll_divr * ext_div * dfs_div;
	do_div(num, denom);

	return (unsigned int)num;
}