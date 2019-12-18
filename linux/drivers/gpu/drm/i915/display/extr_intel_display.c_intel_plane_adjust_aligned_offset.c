#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_3__ {int /*<<< orphan*/  rotation; int /*<<< orphan*/  fb; } ;
struct intel_plane_state {TYPE_2__* color_plane; TYPE_1__ base; } ;
struct TYPE_4__ {int /*<<< orphan*/  stride; } ;

/* Variables and functions */
 int /*<<< orphan*/  intel_adjust_aligned_offset (int*,int*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 intel_plane_adjust_aligned_offset(int *x, int *y,
					     const struct intel_plane_state *state,
					     int color_plane,
					     u32 old_offset, u32 new_offset)
{
	return intel_adjust_aligned_offset(x, y, state->base.fb, color_plane,
					   state->base.rotation,
					   state->color_plane[color_plane].stride,
					   old_offset, new_offset);
}