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
struct TYPE_4__ {scalar_t__ allocated; } ;
struct vc4_plane_state {int /*<<< orphan*/  base; struct drm_plane_state* dlist; TYPE_2__ lbm; } ;
struct vc4_dev {TYPE_1__* hvs; } ;
struct drm_plane_state {int dummy; } ;
struct drm_plane {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  mm_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  __drm_atomic_helper_plane_destroy_state (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_mm_remove_node (TYPE_2__*) ; 
 int /*<<< orphan*/  kfree (struct drm_plane_state*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct vc4_dev* to_vc4_dev (int /*<<< orphan*/ ) ; 
 struct vc4_plane_state* to_vc4_plane_state (struct drm_plane_state*) ; 

__attribute__((used)) static void vc4_plane_destroy_state(struct drm_plane *plane,
				    struct drm_plane_state *state)
{
	struct vc4_dev *vc4 = to_vc4_dev(plane->dev);
	struct vc4_plane_state *vc4_state = to_vc4_plane_state(state);

	if (vc4_state->lbm.allocated) {
		unsigned long irqflags;

		spin_lock_irqsave(&vc4->hvs->mm_lock, irqflags);
		drm_mm_remove_node(&vc4_state->lbm);
		spin_unlock_irqrestore(&vc4->hvs->mm_lock, irqflags);
	}

	kfree(vc4_state->dlist);
	__drm_atomic_helper_plane_destroy_state(&vc4_state->base);
	kfree(state);
}