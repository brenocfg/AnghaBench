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
typedef  int /*<<< orphan*/  u32 ;
struct gk20a_pll {int m; } ;
struct gk20a_clk {int parent_rate; TYPE_1__* params; } ;
struct TYPE_2__ {int min_vco; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIV_ROUND_UP (int,int) ; 
 int KHZ ; 

__attribute__((used)) static inline u32
gk20a_pllg_n_lo(struct gk20a_clk *clk, struct gk20a_pll *pll)
{
	return DIV_ROUND_UP(pll->m * clk->params->min_vco,
			    clk->parent_rate / KHZ);
}