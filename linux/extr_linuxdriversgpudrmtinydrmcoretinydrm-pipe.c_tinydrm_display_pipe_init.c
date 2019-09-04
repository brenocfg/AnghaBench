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
typedef  int /*<<< orphan*/  uint32_t ;
struct tinydrm_device {int /*<<< orphan*/  pipe; struct drm_device* drm; } ;
struct drm_simple_display_pipe_funcs {int dummy; } ;
struct drm_display_mode {int /*<<< orphan*/  vdisplay; int /*<<< orphan*/  hdisplay; } ;
struct TYPE_2__ {int /*<<< orphan*/  max_height; int /*<<< orphan*/  min_height; int /*<<< orphan*/  max_width; int /*<<< orphan*/  min_width; } ;
struct drm_device {TYPE_1__ mode_config; } ;
struct drm_connector {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*,unsigned int) ; 
 int EINVAL ; 
 scalar_t__ IS_ERR (struct drm_connector*) ; 
 int PTR_ERR (struct drm_connector*) ; 
 int /*<<< orphan*/  drm_mode_copy (struct drm_display_mode*,struct drm_display_mode const*) ; 
 int drm_simple_display_pipe_init (struct drm_device*,int /*<<< orphan*/ *,struct drm_simple_display_pipe_funcs const*,int /*<<< orphan*/  const*,unsigned int,int /*<<< orphan*/ *,struct drm_connector*) ; 
 struct drm_connector* tinydrm_connector_create (struct drm_device*,struct drm_display_mode*,int) ; 
 int tinydrm_rotate_mode (struct drm_display_mode*,unsigned int) ; 

int
tinydrm_display_pipe_init(struct tinydrm_device *tdev,
			  const struct drm_simple_display_pipe_funcs *funcs,
			  int connector_type,
			  const uint32_t *formats,
			  unsigned int format_count,
			  const struct drm_display_mode *mode,
			  unsigned int rotation)
{
	struct drm_device *drm = tdev->drm;
	struct drm_display_mode mode_copy;
	struct drm_connector *connector;
	int ret;

	drm_mode_copy(&mode_copy, mode);
	ret = tinydrm_rotate_mode(&mode_copy, rotation);
	if (ret) {
		DRM_ERROR("Illegal rotation value %u\n", rotation);
		return -EINVAL;
	}

	drm->mode_config.min_width = mode_copy.hdisplay;
	drm->mode_config.max_width = mode_copy.hdisplay;
	drm->mode_config.min_height = mode_copy.vdisplay;
	drm->mode_config.max_height = mode_copy.vdisplay;

	connector = tinydrm_connector_create(drm, &mode_copy, connector_type);
	if (IS_ERR(connector))
		return PTR_ERR(connector);

	return drm_simple_display_pipe_init(drm, &tdev->pipe, funcs, formats,
					    format_count, NULL, connector);
}