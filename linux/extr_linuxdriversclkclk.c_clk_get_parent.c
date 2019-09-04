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
struct clk {TYPE_3__* core; } ;
struct TYPE_6__ {TYPE_2__* parent; } ;
struct TYPE_5__ {TYPE_1__* hw; } ;
struct TYPE_4__ {struct clk* clk; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_prepare_lock () ; 
 int /*<<< orphan*/  clk_prepare_unlock () ; 

struct clk *clk_get_parent(struct clk *clk)
{
	struct clk *parent;

	if (!clk)
		return NULL;

	clk_prepare_lock();
	/* TODO: Create a per-user clk and change callers to call clk_put */
	parent = !clk->core->parent ? NULL : clk->core->parent->hw->clk;
	clk_prepare_unlock();

	return parent;
}