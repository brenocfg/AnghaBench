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
struct clk_hw {int dummy; } ;
struct ccu_mux_internal {int dummy; } ;
struct TYPE_6__ {int features; } ;
struct TYPE_5__ {int width; scalar_t__ max; } ;
struct TYPE_4__ {int width; scalar_t__ max; } ;
struct ccu_mp {unsigned long fixed_post_div; TYPE_3__ common; TYPE_2__ p; TYPE_1__ m; } ;

/* Variables and functions */
 int CCU_FEATURE_FIXED_POSTDIV ; 
 int /*<<< orphan*/  ccu_mp_find_best (unsigned long,unsigned long,unsigned int,unsigned int,unsigned int*,unsigned int*) ; 

__attribute__((used)) static unsigned long ccu_mp_round_rate(struct ccu_mux_internal *mux,
				       struct clk_hw *hw,
				       unsigned long *parent_rate,
				       unsigned long rate,
				       void *data)
{
	struct ccu_mp *cmp = data;
	unsigned int max_m, max_p;
	unsigned int m, p;

	if (cmp->common.features & CCU_FEATURE_FIXED_POSTDIV)
		rate *= cmp->fixed_post_div;

	max_m = cmp->m.max ?: 1 << cmp->m.width;
	max_p = cmp->p.max ?: 1 << ((1 << cmp->p.width) - 1);

	ccu_mp_find_best(*parent_rate, rate, max_m, max_p, &m, &p);
	rate = *parent_rate / p / m;

	if (cmp->common.features & CCU_FEATURE_FIXED_POSTDIV)
		rate /= cmp->fixed_post_div;

	return rate;
}