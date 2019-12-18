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
typedef  int /*<<< orphan*/  u32 ;
struct intel_plane_state {int /*<<< orphan*/  vma; } ;

/* Variables and functions */
 int /*<<< orphan*/  i915_ggtt_offset (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline u32 intel_plane_ggtt_offset(const struct intel_plane_state *state)
{
	return i915_ggtt_offset(state->vma);
}