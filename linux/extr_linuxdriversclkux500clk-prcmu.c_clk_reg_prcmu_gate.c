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
typedef  int /*<<< orphan*/  u8 ;
struct clk {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_prcmu_gate_ops ; 
 struct clk* clk_reg_prcmu (char const*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ *) ; 

struct clk *clk_reg_prcmu_gate(const char *name,
			       const char *parent_name,
			       u8 cg_sel,
			       unsigned long flags)
{
	return clk_reg_prcmu(name, parent_name, cg_sel, 0, flags,
			&clk_prcmu_gate_ops);
}