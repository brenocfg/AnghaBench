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
 struct i915_request* i915_active_request_raw (struct i915_active_request const*,struct mutex*) ; 
 scalar_t__ i915_request_completed (struct i915_request*) ; 

__attribute__((used)) static inline struct i915_request *
i915_active_request_peek(const struct i915_active_request *active,
			 struct mutex *mutex)
{
	struct i915_request *request;

	request = i915_active_request_raw(active, mutex);
	if (!request || i915_request_completed(request))
		return NULL;

	return request;
}