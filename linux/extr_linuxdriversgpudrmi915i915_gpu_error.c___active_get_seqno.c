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
typedef  int /*<<< orphan*/  uint32_t ;
struct i915_request {int /*<<< orphan*/  global_seqno; } ;
struct i915_gem_active {int dummy; } ;

/* Variables and functions */
 struct i915_request* __i915_gem_active_peek (struct i915_gem_active*) ; 

__attribute__((used)) static inline uint32_t
__active_get_seqno(struct i915_gem_active *active)
{
	struct i915_request *request;

	request = __i915_gem_active_peek(active);
	return request ? request->global_seqno : 0;
}