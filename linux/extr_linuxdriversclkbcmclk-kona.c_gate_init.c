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
 int __gate_commit (struct ccu_data*,struct bcm_clk_gate*) ; 
 int /*<<< orphan*/  gate_exists (struct bcm_clk_gate*) ; 

__attribute__((used)) static bool gate_init(struct ccu_data *ccu, struct bcm_clk_gate *gate)
{
	if (!gate_exists(gate))
		return true;
	return __gate_commit(ccu, gate);
}