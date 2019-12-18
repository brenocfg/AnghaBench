#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct llist_node {int dummy; } ;
struct llist_head {int dummy; } ;
struct intel_engine_cs {TYPE_1__* i915; int /*<<< orphan*/  uabi_node; } ;
struct TYPE_2__ {int /*<<< orphan*/  uabi_engines; } ;

/* Variables and functions */
 int /*<<< orphan*/  llist_add (struct llist_node*,struct llist_head*) ; 

void intel_engine_add_user(struct intel_engine_cs *engine)
{
	llist_add((struct llist_node *)&engine->uabi_node,
		  (struct llist_head *)&engine->i915->uabi_engines);
}