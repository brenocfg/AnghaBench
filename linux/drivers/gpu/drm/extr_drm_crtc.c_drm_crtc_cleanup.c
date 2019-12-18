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
struct TYPE_3__ {int /*<<< orphan*/  num_crtc; } ;
struct drm_device {TYPE_1__ mode_config; } ;
struct drm_crtc {int /*<<< orphan*/ * name; scalar_t__ state; TYPE_2__* funcs; int /*<<< orphan*/  head; int /*<<< orphan*/  base; int /*<<< orphan*/  mutex; int /*<<< orphan*/ * gamma_store; struct drm_device* dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* atomic_destroy_state ) (struct drm_crtc*,scalar_t__) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  drm_crtc_crc_fini (struct drm_crtc*) ; 
 int /*<<< orphan*/  drm_mode_object_unregister (struct drm_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_modeset_lock_fini (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct drm_crtc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (struct drm_crtc*,scalar_t__) ; 

void drm_crtc_cleanup(struct drm_crtc *crtc)
{
	struct drm_device *dev = crtc->dev;

	/* Note that the crtc_list is considered to be static; should we
	 * remove the drm_crtc at runtime we would have to decrement all
	 * the indices on the drm_crtc after us in the crtc_list.
	 */

	drm_crtc_crc_fini(crtc);

	kfree(crtc->gamma_store);
	crtc->gamma_store = NULL;

	drm_modeset_lock_fini(&crtc->mutex);

	drm_mode_object_unregister(dev, &crtc->base);
	list_del(&crtc->head);
	dev->mode_config.num_crtc--;

	WARN_ON(crtc->state && !crtc->funcs->atomic_destroy_state);
	if (crtc->state && crtc->funcs->atomic_destroy_state)
		crtc->funcs->atomic_destroy_state(crtc, crtc->state);

	kfree(crtc->name);

	memset(crtc, 0, sizeof(*crtc));
}