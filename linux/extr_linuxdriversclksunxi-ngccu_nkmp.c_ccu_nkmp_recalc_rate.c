#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned long u32 ;
struct clk_hw {int dummy; } ;
struct TYPE_10__ {int features; scalar_t__ reg; scalar_t__ base; } ;
struct TYPE_9__ {unsigned long shift; int width; } ;
struct TYPE_8__ {unsigned long shift; int width; scalar_t__ offset; } ;
struct TYPE_7__ {unsigned long shift; int width; scalar_t__ offset; } ;
struct TYPE_6__ {unsigned long shift; int width; scalar_t__ offset; } ;
struct ccu_nkmp {unsigned long fixed_post_div; TYPE_5__ common; TYPE_4__ p; TYPE_3__ m; TYPE_2__ k; TYPE_1__ n; } ;

/* Variables and functions */
 int CCU_FEATURE_FIXED_POSTDIV ; 
 unsigned long ccu_nkmp_calc_rate (unsigned long,unsigned long,unsigned long,unsigned long,int) ; 
 struct ccu_nkmp* hw_to_ccu_nkmp (struct clk_hw*) ; 
 unsigned long readl (scalar_t__) ; 

__attribute__((used)) static unsigned long ccu_nkmp_recalc_rate(struct clk_hw *hw,
					unsigned long parent_rate)
{
	struct ccu_nkmp *nkmp = hw_to_ccu_nkmp(hw);
	unsigned long n, m, k, p, rate;
	u32 reg;

	reg = readl(nkmp->common.base + nkmp->common.reg);

	n = reg >> nkmp->n.shift;
	n &= (1 << nkmp->n.width) - 1;
	n += nkmp->n.offset;
	if (!n)
		n++;

	k = reg >> nkmp->k.shift;
	k &= (1 << nkmp->k.width) - 1;
	k += nkmp->k.offset;
	if (!k)
		k++;

	m = reg >> nkmp->m.shift;
	m &= (1 << nkmp->m.width) - 1;
	m += nkmp->m.offset;
	if (!m)
		m++;

	p = reg >> nkmp->p.shift;
	p &= (1 << nkmp->p.width) - 1;

	rate = ccu_nkmp_calc_rate(parent_rate, n, k, m, 1 << p);
	if (nkmp->common.features & CCU_FEATURE_FIXED_POSTDIV)
		rate /= nkmp->fixed_post_div;

	return rate;
}