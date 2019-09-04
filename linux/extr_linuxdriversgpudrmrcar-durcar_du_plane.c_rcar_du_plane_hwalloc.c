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
struct rcar_du_plane_state {scalar_t__ source; TYPE_2__* format; } ;
struct rcar_du_plane {TYPE_1__* group; } ;
struct TYPE_4__ {unsigned int planes; } ;
struct TYPE_3__ {scalar_t__ index; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int RCAR_DU_NUM_HW_PLANES ; 
 scalar_t__ RCAR_DU_PLANE_VSPD0 ; 
 scalar_t__ RCAR_DU_PLANE_VSPD1 ; 

__attribute__((used)) static int rcar_du_plane_hwalloc(struct rcar_du_plane *plane,
				 struct rcar_du_plane_state *state,
				 unsigned int free)
{
	unsigned int num_planes = state->format->planes;
	int fixed = -1;
	int i;

	if (state->source == RCAR_DU_PLANE_VSPD0) {
		/* VSPD0 feeds plane 0 on DU0/1. */
		if (plane->group->index != 0)
			return -EINVAL;

		fixed = 0;
	} else if (state->source == RCAR_DU_PLANE_VSPD1) {
		/* VSPD1 feeds plane 1 on DU0/1 or plane 0 on DU2. */
		fixed = plane->group->index == 0 ? 1 : 0;
	}

	if (fixed >= 0)
		return free & (1 << fixed) ? fixed : -EBUSY;

	for (i = RCAR_DU_NUM_HW_PLANES - 1; i >= 0; --i) {
		if (!(free & (1 << i)))
			continue;

		if (num_planes == 1 || free & (1 << ((i + 1) % 8)))
			break;
	}

	return i < 0 ? -EBUSY : i;
}