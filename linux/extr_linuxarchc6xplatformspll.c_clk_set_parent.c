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
struct clk {int /*<<< orphan*/  (* recalc ) (struct clk*) ;int /*<<< orphan*/  rate; int /*<<< orphan*/  children; struct clk* parent; int /*<<< orphan*/  childnode; int /*<<< orphan*/  usecount; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ IS_ERR (struct clk*) ; 
 scalar_t__ WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clockfw_lock ; 
 int /*<<< orphan*/  clocks_mutex ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  propagate_rate (struct clk*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct clk*) ; 

int clk_set_parent(struct clk *clk, struct clk *parent)
{
	unsigned long flags;

	if (clk == NULL || IS_ERR(clk))
		return -EINVAL;

	/* Cannot change parent on enabled clock */
	if (WARN_ON(clk->usecount))
		return -EINVAL;

	mutex_lock(&clocks_mutex);
	clk->parent = parent;
	list_del_init(&clk->childnode);
	list_add(&clk->childnode, &clk->parent->children);
	mutex_unlock(&clocks_mutex);

	spin_lock_irqsave(&clockfw_lock, flags);
	if (clk->recalc)
		clk->rate = clk->recalc(clk);
	propagate_rate(clk);
	spin_unlock_irqrestore(&clockfw_lock, flags);

	return 0;
}