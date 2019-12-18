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
 struct i915_request* mock_request (struct intel_context*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct i915_request *
__mock_request_alloc(struct intel_context *ce)
{
	return mock_request(ce, 0);
}