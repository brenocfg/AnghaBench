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
struct ccu_data {int dummy; } ;
struct bcm_clk_trig {int dummy; } ;
struct bcm_clk_gate {int dummy; } ;
struct bcm_clk_div {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __div_commit (struct ccu_data*,struct bcm_clk_gate*,struct bcm_clk_div*,struct bcm_clk_trig*) ; 
 int /*<<< orphan*/  divider_exists (struct bcm_clk_div*) ; 
 scalar_t__ divider_is_fixed (struct bcm_clk_div*) ; 

__attribute__((used)) static bool div_init(struct ccu_data *ccu, struct bcm_clk_gate *gate,
			struct bcm_clk_div *div, struct bcm_clk_trig *trig)
{
	if (!divider_exists(div) || divider_is_fixed(div))
		return true;
	return !__div_commit(ccu, gate, div, trig);
}