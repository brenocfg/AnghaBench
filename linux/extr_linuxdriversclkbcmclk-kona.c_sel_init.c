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
struct bcm_clk_sel {int dummy; } ;
struct bcm_clk_gate {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __sel_commit (struct ccu_data*,struct bcm_clk_gate*,struct bcm_clk_sel*,struct bcm_clk_trig*) ; 
 int /*<<< orphan*/  selector_exists (struct bcm_clk_sel*) ; 

__attribute__((used)) static bool sel_init(struct ccu_data *ccu, struct bcm_clk_gate *gate,
			struct bcm_clk_sel *sel, struct bcm_clk_trig *trig)
{
	if (!selector_exists(sel))
		return true;
	return !__sel_commit(ccu, gate, sel, trig);
}