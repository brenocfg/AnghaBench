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
struct i915_sched_node {int dummy; } ;

/* Variables and functions */
 int i915_request_started (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  node_to_request (struct i915_sched_node const*) ; 

__attribute__((used)) static inline bool node_started(const struct i915_sched_node *node)
{
	return i915_request_started(node_to_request(node));
}