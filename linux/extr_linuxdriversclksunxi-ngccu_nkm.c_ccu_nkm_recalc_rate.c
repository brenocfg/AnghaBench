#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned long u32 ;
struct clk_hw {int dummy; } ;
struct TYPE_8__ {int features; scalar_t__ reg; scalar_t__ base; } ;
struct TYPE_7__ {unsigned long shift; int width; scalar_t__ offset; } ;
struct TYPE_6__ {unsigned long shift; int width; scalar_t__ offset; } ;
struct TYPE_5__ {unsigned long shift; int width; scalar_t__ offset; } ;
struct ccu_nkm {unsigned long fixed_post_div; TYPE_4__ common; TYPE_3__ m; TYPE_2__ k; TYPE_1__ n; } ;

/* Variables and functions */
 int CCU_FEATURE_FIXED_POSTDIV ; 
 struct ccu_nkm* hw_to_ccu_nkm (struct clk_hw*) ; 
 unsigned long readl (scalar_t__) ; 

__attribute__((used)) static unsigned long ccu_nkm_recalc_rate(struct clk_hw *hw,
					unsigned long parent_rate)
{
	struct ccu_nkm *nkm = hw_to_ccu_nkm(hw);
	unsigned long n, m, k, rate;
	u32 reg;

	reg = readl(nkm->common.base + nkm->common.reg);

	n = reg >> nkm->n.shift;
	n &= (1 << nkm->n.width) - 1;
	n += nkm->n.offset;
	if (!n)
		n++;

	k = reg >> nkm->k.shift;
	k &= (1 << nkm->k.width) - 1;
	k += nkm->k.offset;
	if (!k)
		k++;

	m = reg >> nkm->m.shift;
	m &= (1 << nkm->m.width) - 1;
	m += nkm->m.offset;
	if (!m)
		m++;

	rate = parent_rate * n  * k / m;

	if (nkm->common.features & CCU_FEATURE_FIXED_POSTDIV)
		rate /= nkm->fixed_post_div;

	return rate;
}