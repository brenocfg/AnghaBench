#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned long u32 ;
struct clk_hw {int dummy; } ;
struct TYPE_6__ {int features; scalar_t__ reg; scalar_t__ base; } ;
struct TYPE_5__ {unsigned long shift; int width; scalar_t__ offset; } ;
struct TYPE_4__ {unsigned long shift; int width; scalar_t__ offset; } ;
struct ccu_nk {unsigned long fixed_post_div; TYPE_3__ common; TYPE_2__ k; TYPE_1__ n; } ;

/* Variables and functions */
 int CCU_FEATURE_FIXED_POSTDIV ; 
 struct ccu_nk* hw_to_ccu_nk (struct clk_hw*) ; 
 unsigned long readl (scalar_t__) ; 

__attribute__((used)) static unsigned long ccu_nk_recalc_rate(struct clk_hw *hw,
					unsigned long parent_rate)
{
	struct ccu_nk *nk = hw_to_ccu_nk(hw);
	unsigned long rate, n, k;
	u32 reg;

	reg = readl(nk->common.base + nk->common.reg);

	n = reg >> nk->n.shift;
	n &= (1 << nk->n.width) - 1;
	n += nk->n.offset;
	if (!n)
		n++;

	k = reg >> nk->k.shift;
	k &= (1 << nk->k.width) - 1;
	k += nk->k.offset;
	if (!k)
		k++;

	rate = parent_rate * n * k;
	if (nk->common.features & CCU_FEATURE_FIXED_POSTDIV)
		rate /= nk->fixed_post_div;

	return rate;
}