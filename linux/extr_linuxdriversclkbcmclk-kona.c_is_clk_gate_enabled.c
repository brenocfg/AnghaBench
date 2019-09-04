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
struct bcm_clk_gate {int dummy; } ;

/* Variables and functions */
 int __is_clk_gate_enabled (struct ccu_data*,struct bcm_clk_gate*) ; 
 long ccu_lock (struct ccu_data*) ; 
 int /*<<< orphan*/  ccu_unlock (struct ccu_data*,long) ; 
 int /*<<< orphan*/  gate_exists (struct bcm_clk_gate*) ; 

__attribute__((used)) static bool
is_clk_gate_enabled(struct ccu_data *ccu, struct bcm_clk_gate *gate)
{
	long flags;
	bool ret;

	/* Avoid taking the lock if we can */
	if (!gate_exists(gate))
		return true;

	flags = ccu_lock(ccu);
	ret = __is_clk_gate_enabled(ccu, gate);
	ccu_unlock(ccu, flags);

	return ret;
}