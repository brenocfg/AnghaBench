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
struct i915_request {int dummy; } ;
struct i915_active_request {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  ref; } ;

/* Variables and functions */
 int /*<<< orphan*/  active_retire (int /*<<< orphan*/ ) ; 
 TYPE_1__* node_from_active (struct i915_active_request*) ; 

__attribute__((used)) static void
node_retire(struct i915_active_request *base, struct i915_request *rq)
{
	active_retire(node_from_active(base)->ref);
}