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
struct drm_display_mode {int dummy; } ;
struct TYPE_3__ {size_t mode; } ;
struct drm_connector_state {TYPE_1__ tv; } ;
struct drm_connector {int /*<<< orphan*/  dev; struct drm_connector_state* state; } ;
struct TYPE_4__ {int /*<<< orphan*/  mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int ENOMEM ; 
 struct drm_display_mode* drm_mode_duplicate (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_mode_probed_add (struct drm_connector*,struct drm_display_mode*) ; 
 TYPE_2__* vc4_vec_tv_modes ; 

__attribute__((used)) static int vc4_vec_connector_get_modes(struct drm_connector *connector)
{
	struct drm_connector_state *state = connector->state;
	struct drm_display_mode *mode;

	mode = drm_mode_duplicate(connector->dev,
				  vc4_vec_tv_modes[state->tv.mode].mode);
	if (!mode) {
		DRM_ERROR("Failed to create a new display mode\n");
		return -ENOMEM;
	}

	drm_mode_probed_add(connector, mode);

	return 1;
}