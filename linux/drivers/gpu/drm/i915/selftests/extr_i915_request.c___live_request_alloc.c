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
struct intel_context {int dummy; } ;
struct i915_request {int dummy; } ;

/* Variables and functions */
 struct i915_request* intel_context_create_request (struct intel_context*) ; 

__attribute__((used)) static struct i915_request *
__live_request_alloc(struct intel_context *ce)
{
	return intel_context_create_request(ce);
}