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
struct drm_plane {int /*<<< orphan*/  name; scalar_t__ state; TYPE_2__* funcs; int /*<<< orphan*/  head; int /*<<< orphan*/  base; int /*<<< orphan*/  modifiers; int /*<<< orphan*/  format_types; int /*<<< orphan*/  mutex; struct drm_device* dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  num_total_plane; } ;
struct drm_device {TYPE_1__ mode_config; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* atomic_destroy_state ) (struct drm_plane*,scalar_t__) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  drm_mode_object_unregister (struct drm_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_modeset_lock_fini (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct drm_plane*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (struct drm_plane*,scalar_t__) ; 

void drm_plane_cleanup(struct drm_plane *plane)
{
	struct drm_device *dev = plane->dev;

	drm_modeset_lock_fini(&plane->mutex);

	kfree(plane->format_types);
	kfree(plane->modifiers);
	drm_mode_object_unregister(dev, &plane->base);

	BUG_ON(list_empty(&plane->head));

	/* Note that the plane_list is considered to be static; should we
	 * remove the drm_plane at runtime we would have to decrement all
	 * the indices on the drm_plane after us in the plane_list.
	 */

	list_del(&plane->head);
	dev->mode_config.num_total_plane--;

	WARN_ON(plane->state && !plane->funcs->atomic_destroy_state);
	if (plane->state && plane->funcs->atomic_destroy_state)
		plane->funcs->atomic_destroy_state(plane, plane->state);

	kfree(plane->name);

	memset(plane, 0, sizeof(*plane));
}