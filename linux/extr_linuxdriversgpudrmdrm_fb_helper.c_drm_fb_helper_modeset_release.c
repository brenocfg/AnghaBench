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
struct drm_mode_set {int num_connectors; int /*<<< orphan*/ * fb; int /*<<< orphan*/ * mode; int /*<<< orphan*/ ** connectors; } ;
struct drm_fb_helper {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_connector_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_mode_destroy (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void drm_fb_helper_modeset_release(struct drm_fb_helper *helper,
					  struct drm_mode_set *modeset)
{
	int i;

	for (i = 0; i < modeset->num_connectors; i++) {
		drm_connector_put(modeset->connectors[i]);
		modeset->connectors[i] = NULL;
	}
	modeset->num_connectors = 0;

	drm_mode_destroy(helper->dev, modeset->mode);
	modeset->mode = NULL;

	/* FIXME should hold a ref? */
	modeset->fb = NULL;
}