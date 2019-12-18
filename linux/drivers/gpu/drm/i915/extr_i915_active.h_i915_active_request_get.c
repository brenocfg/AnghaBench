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
struct mutex {int dummy; } ;
struct i915_request {int dummy; } ;
struct i915_active_request {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  i915_active_request_peek (struct i915_active_request const*,struct mutex*) ; 
 struct i915_request* i915_request_get (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline struct i915_request *
i915_active_request_get(const struct i915_active_request *active,
			struct mutex *mutex)
{
	return i915_request_get(i915_active_request_peek(active, mutex));
}