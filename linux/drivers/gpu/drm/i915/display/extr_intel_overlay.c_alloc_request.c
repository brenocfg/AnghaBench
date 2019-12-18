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
struct intel_overlay {void (* flip_complete ) (struct intel_overlay*) ;int /*<<< orphan*/  last_flip; int /*<<< orphan*/  context; } ;
struct i915_request {int /*<<< orphan*/  timeline; } ;

/* Variables and functions */
 struct i915_request* ERR_PTR (int) ; 
 scalar_t__ IS_ERR (struct i915_request*) ; 
 int i915_active_ref (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct i915_request*) ; 
 int /*<<< orphan*/  i915_request_add (struct i915_request*) ; 
 struct i915_request* i915_request_create (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct i915_request *
alloc_request(struct intel_overlay *overlay, void (*fn)(struct intel_overlay *))
{
	struct i915_request *rq;
	int err;

	overlay->flip_complete = fn;

	rq = i915_request_create(overlay->context);
	if (IS_ERR(rq))
		return rq;

	err = i915_active_ref(&overlay->last_flip, rq->timeline, rq);
	if (err) {
		i915_request_add(rq);
		return ERR_PTR(err);
	}

	return rq;
}