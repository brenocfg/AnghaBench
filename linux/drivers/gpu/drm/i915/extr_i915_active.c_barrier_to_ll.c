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
struct TYPE_2__ {int /*<<< orphan*/  link; } ;
struct active_node {TYPE_1__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  GEM_BUG_ON (int) ; 
 int /*<<< orphan*/  is_barrier (TYPE_1__*) ; 

__attribute__((used)) static inline struct llist_node *barrier_to_ll(struct active_node *node)
{
	GEM_BUG_ON(!is_barrier(&node->base));
	return (struct llist_node *)&node->base.link;
}