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
struct intel_context {int dummy; } ;
struct TYPE_2__ {unsigned long delay; } ;
struct i915_request {TYPE_1__ mock; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct i915_request*) ; 
 struct i915_request* intel_context_create_request (struct intel_context*) ; 

struct i915_request *
mock_request(struct intel_context *ce, unsigned long delay)
{
	struct i915_request *request;

	/* NB the i915->requests slab cache is enlarged to fit mock_request */
	request = intel_context_create_request(ce);
	if (IS_ERR(request))
		return NULL;

	request->mock.delay = delay;
	return request;
}