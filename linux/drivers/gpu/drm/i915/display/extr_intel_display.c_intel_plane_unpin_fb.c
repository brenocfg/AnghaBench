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
struct intel_plane_state {int /*<<< orphan*/  flags; int /*<<< orphan*/  vma; } ;
struct i915_vma {int dummy; } ;

/* Variables and functions */
 struct i915_vma* fetch_and_zero (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  intel_unpin_fb_vma (struct i915_vma*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void intel_plane_unpin_fb(struct intel_plane_state *old_plane_state)
{
	struct i915_vma *vma;

	vma = fetch_and_zero(&old_plane_state->vma);
	if (vma)
		intel_unpin_fb_vma(vma, old_plane_state->flags);
}