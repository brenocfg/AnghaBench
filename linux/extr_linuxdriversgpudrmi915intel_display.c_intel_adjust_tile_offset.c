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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {int /*<<< orphan*/  rotation; int /*<<< orphan*/  fb; } ;
struct intel_plane_state {TYPE_1__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  _intel_adjust_tile_offset (int*,int*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 intel_adjust_tile_offset(int *x, int *y,
				    const struct intel_plane_state *state, int plane,
				    u32 old_offset, u32 new_offset)
{
	return _intel_adjust_tile_offset(x, y, state->base.fb, plane,
					 state->base.rotation,
					 old_offset, new_offset);
}