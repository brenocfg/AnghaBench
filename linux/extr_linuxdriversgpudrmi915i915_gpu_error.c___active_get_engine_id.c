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
struct i915_request {TYPE_1__* engine; } ;
struct i915_gem_active {int dummy; } ;
struct TYPE_2__ {int id; } ;

/* Variables and functions */
 struct i915_request* __i915_gem_active_peek (struct i915_gem_active*) ; 

__attribute__((used)) static inline int
__active_get_engine_id(struct i915_gem_active *active)
{
	struct i915_request *request;

	request = __i915_gem_active_peek(active);
	return request ? request->engine->id : -1;
}