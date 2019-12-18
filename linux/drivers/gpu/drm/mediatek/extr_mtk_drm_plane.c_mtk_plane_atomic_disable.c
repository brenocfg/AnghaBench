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
struct TYPE_2__ {int enable; int dirty; } ;
struct mtk_plane_state {TYPE_1__ pending; } ;
struct drm_plane_state {int dummy; } ;
struct drm_plane {int /*<<< orphan*/  state; } ;

/* Variables and functions */
 struct mtk_plane_state* to_mtk_plane_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static void mtk_plane_atomic_disable(struct drm_plane *plane,
				     struct drm_plane_state *old_state)
{
	struct mtk_plane_state *state = to_mtk_plane_state(plane->state);

	state->pending.enable = false;
	wmb(); /* Make sure the above parameter is set before update */
	state->pending.dirty = true;
}