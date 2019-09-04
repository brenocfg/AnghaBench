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
struct intel_breadcrumbs {int /*<<< orphan*/  waiters; scalar_t__ irq_wait; } ;
struct intel_engine_cs {struct intel_breadcrumbs breadcrumbs; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  RB_EMPTY_ROOT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*) ; 

__attribute__((used)) static int check_rbtree_empty(struct intel_engine_cs *engine)
{
	struct intel_breadcrumbs *b = &engine->breadcrumbs;

	if (b->irq_wait) {
		pr_err("Empty breadcrumbs still has a waiter\n");
		return -EINVAL;
	}

	if (!RB_EMPTY_ROOT(&b->waiters)) {
		pr_err("Empty breadcrumbs, but wait-tree not empty\n");
		return -EINVAL;
	}

	return 0;
}