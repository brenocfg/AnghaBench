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
struct i915_request {int /*<<< orphan*/  reserved_space; int /*<<< orphan*/  ring; TYPE_1__* hw_context; } ;
struct TYPE_2__ {int /*<<< orphan*/  pin_count; } ;

/* Variables and functions */
 scalar_t__ EXECLISTS_REQUEST_SIZE ; 
 int /*<<< orphan*/  GEM_BUG_ON (int) ; 
 int intel_ring_wait_for_space (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int execlists_request_alloc(struct i915_request *request)
{
	int ret;

	GEM_BUG_ON(!request->hw_context->pin_count);

	/* Flush enough space to reduce the likelihood of waiting after
	 * we start building the request - in which case we will just
	 * have to repeat work.
	 */
	request->reserved_space += EXECLISTS_REQUEST_SIZE;

	ret = intel_ring_wait_for_space(request->ring, request->reserved_space);
	if (ret)
		return ret;

	/* Note that after this point, we have committed to using
	 * this request as it is being used to both track the
	 * state of engine initialisation and liveness of the
	 * golden renderstate above. Think twice before you try
	 * to cancel/unwind this request now.
	 */

	request->reserved_space -= EXECLISTS_REQUEST_SIZE;
	return 0;
}