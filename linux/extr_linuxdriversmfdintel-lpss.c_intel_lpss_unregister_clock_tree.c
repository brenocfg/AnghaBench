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
struct clk {int dummy; } ;

/* Variables and functions */
 struct clk* clk_get_parent (struct clk*) ; 
 int /*<<< orphan*/  clk_unregister (struct clk*) ; 

__attribute__((used)) static void intel_lpss_unregister_clock_tree(struct clk *clk)
{
	struct clk *parent;

	while (clk) {
		parent = clk_get_parent(clk);
		clk_unregister(clk);
		clk = parent;
	}
}