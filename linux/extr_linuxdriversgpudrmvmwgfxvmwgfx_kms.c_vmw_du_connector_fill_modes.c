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
typedef  scalar_t__ uint32_t ;
typedef  int u32 ;
struct vmw_private {scalar_t__ active_display_unit; int /*<<< orphan*/  stdu_max_height; int /*<<< orphan*/  stdu_max_width; int /*<<< orphan*/  texture_max_height; int /*<<< orphan*/  texture_max_width; scalar_t__ assume_16bpp; } ;
struct vmw_display_unit {int pref_width; scalar_t__ pref_height; struct drm_display_mode* pref_mode; } ;
struct drm_display_mode {int hdisplay; scalar_t__ vdisplay; scalar_t__ type; int /*<<< orphan*/  vrefresh; int /*<<< orphan*/  head; int /*<<< orphan*/  member_0; } ;
struct drm_device {int dummy; } ;
struct drm_connector {int /*<<< orphan*/  modes; struct drm_device* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_MODE (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int DRM_MODE_FLAG_NHSYNC ; 
 int DRM_MODE_FLAG_PVSYNC ; 
 int DRM_MODE_TYPE_DRIVER ; 
 int DRM_MODE_TYPE_PREFERRED ; 
 int /*<<< orphan*/  drm_connector_list_update (struct drm_connector*) ; 
 int /*<<< orphan*/  drm_mode_destroy (struct drm_device*,struct drm_display_mode*) ; 
 struct drm_display_mode* drm_mode_duplicate (struct drm_device*,struct drm_display_mode*) ; 
 int /*<<< orphan*/  drm_mode_probed_add (struct drm_connector*,struct drm_display_mode*) ; 
 int /*<<< orphan*/  drm_mode_sort (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_mode_vrefresh (struct drm_display_mode*) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 scalar_t__ min (scalar_t__,int /*<<< orphan*/ ) ; 
 struct vmw_display_unit* vmw_connector_to_du (struct drm_connector*) ; 
 scalar_t__ vmw_du_screen_target ; 
 int /*<<< orphan*/  vmw_guess_mode_timing (struct drm_display_mode*) ; 
 struct drm_display_mode* vmw_kms_connector_builtin ; 
 scalar_t__ vmw_kms_validate_mode_vram (struct vmw_private*,int,scalar_t__) ; 
 struct vmw_private* vmw_priv (struct drm_device*) ; 

int vmw_du_connector_fill_modes(struct drm_connector *connector,
				uint32_t max_width, uint32_t max_height)
{
	struct vmw_display_unit *du = vmw_connector_to_du(connector);
	struct drm_device *dev = connector->dev;
	struct vmw_private *dev_priv = vmw_priv(dev);
	struct drm_display_mode *mode = NULL;
	struct drm_display_mode *bmode;
	struct drm_display_mode prefmode = { DRM_MODE("preferred",
		DRM_MODE_TYPE_DRIVER | DRM_MODE_TYPE_PREFERRED,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_PVSYNC)
	};
	int i;
	u32 assumed_bpp = 4;

	if (dev_priv->assume_16bpp)
		assumed_bpp = 2;

	max_width  = min(max_width,  dev_priv->texture_max_width);
	max_height = min(max_height, dev_priv->texture_max_height);

	/*
	 * For STDU extra limit for a mode on SVGA_REG_SCREENTARGET_MAX_WIDTH/
	 * HEIGHT registers.
	 */
	if (dev_priv->active_display_unit == vmw_du_screen_target) {
		max_width  = min(max_width,  dev_priv->stdu_max_width);
		max_height = min(max_height, dev_priv->stdu_max_height);
	}

	/* Add preferred mode */
	mode = drm_mode_duplicate(dev, &prefmode);
	if (!mode)
		return 0;
	mode->hdisplay = du->pref_width;
	mode->vdisplay = du->pref_height;
	vmw_guess_mode_timing(mode);

	if (vmw_kms_validate_mode_vram(dev_priv,
					mode->hdisplay * assumed_bpp,
					mode->vdisplay)) {
		drm_mode_probed_add(connector, mode);
	} else {
		drm_mode_destroy(dev, mode);
		mode = NULL;
	}

	if (du->pref_mode) {
		list_del_init(&du->pref_mode->head);
		drm_mode_destroy(dev, du->pref_mode);
	}

	/* mode might be null here, this is intended */
	du->pref_mode = mode;

	for (i = 0; vmw_kms_connector_builtin[i].type != 0; i++) {
		bmode = &vmw_kms_connector_builtin[i];
		if (bmode->hdisplay > max_width ||
		    bmode->vdisplay > max_height)
			continue;

		if (!vmw_kms_validate_mode_vram(dev_priv,
						bmode->hdisplay * assumed_bpp,
						bmode->vdisplay))
			continue;

		mode = drm_mode_duplicate(dev, bmode);
		if (!mode)
			return 0;
		mode->vrefresh = drm_mode_vrefresh(mode);

		drm_mode_probed_add(connector, mode);
	}

	drm_connector_list_update(connector);
	/* Move the prefered mode first, help apps pick the right mode. */
	drm_mode_sort(&connector->modes);

	return 1;
}