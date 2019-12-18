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
struct intel_context {int /*<<< orphan*/  state; int /*<<< orphan*/  ring; } ;

/* Variables and functions */
 int /*<<< orphan*/  i915_vma_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_ring_put (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __execlists_context_fini(struct intel_context *ce)
{
	intel_ring_put(ce->ring);
	i915_vma_put(ce->state);
}