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
struct i915_request {int dummy; } ;
struct i915_gem_active {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAX_SCHEDULE_TIMEOUT ; 
 struct i915_request* i915_gem_active_get_unlocked (struct i915_gem_active const*) ; 
 int /*<<< orphan*/  i915_request_put (struct i915_request*) ; 
 long i915_request_wait (struct i915_request*,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int
i915_gem_active_wait(const struct i915_gem_active *active, unsigned int flags)
{
	struct i915_request *request;
	long ret = 0;

	request = i915_gem_active_get_unlocked(active);
	if (request) {
		ret = i915_request_wait(request, flags, MAX_SCHEDULE_TIMEOUT);
		i915_request_put(request);
	}

	return ret < 0 ? ret : 0;
}