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
struct i915_active {int dummy; } ;
struct active_node {int dummy; } ;

/* Variables and functions */
 int ____active_del_barrier (struct i915_active*,struct active_node*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  barrier_to_engine (struct active_node*) ; 

__attribute__((used)) static bool
__active_del_barrier(struct i915_active *ref, struct active_node *node)
{
	return ____active_del_barrier(ref, node, barrier_to_engine(node));
}