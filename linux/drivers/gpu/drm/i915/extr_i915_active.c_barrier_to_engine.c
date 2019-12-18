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
struct intel_engine_cs {int dummy; } ;
struct active_node {int /*<<< orphan*/  base; } ;

/* Variables and functions */
 int /*<<< orphan*/  GEM_BUG_ON (int) ; 
 struct intel_engine_cs* __barrier_to_engine (struct active_node*) ; 
 int /*<<< orphan*/  is_barrier (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline struct intel_engine_cs *
barrier_to_engine(struct active_node *node)
{
	GEM_BUG_ON(!is_barrier(&node->base));
	return __barrier_to_engine(node);
}