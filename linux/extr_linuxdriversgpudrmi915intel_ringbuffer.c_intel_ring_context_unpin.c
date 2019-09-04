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
struct intel_context {int /*<<< orphan*/  gem_context; } ;

/* Variables and functions */
 int /*<<< orphan*/  __context_unpin (struct intel_context*) ; 
 int /*<<< orphan*/  __context_unpin_ppgtt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i915_gem_context_put (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void intel_ring_context_unpin(struct intel_context *ce)
{
	__context_unpin_ppgtt(ce->gem_context);
	__context_unpin(ce);

	i915_gem_context_put(ce->gem_context);
}