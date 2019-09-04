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
struct clk {int /*<<< orphan*/  con_id; int /*<<< orphan*/  clks_node; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_prepare_lock () ; 
 int /*<<< orphan*/  clk_prepare_unlock () ; 
 int /*<<< orphan*/  hlist_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct clk*) ; 
 int /*<<< orphan*/  kfree_const (int /*<<< orphan*/ ) ; 

void __clk_free_clk(struct clk *clk)
{
	clk_prepare_lock();
	hlist_del(&clk->clks_node);
	clk_prepare_unlock();

	kfree_const(clk->con_id);
	kfree(clk);
}