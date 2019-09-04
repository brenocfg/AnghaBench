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
typedef  int /*<<< orphan*/  u16 ;
struct tinydrm_device {TYPE_2__* drm; int /*<<< orphan*/  fb_dirty; } ;
struct mipi_dbi {unsigned int rotation; int /*<<< orphan*/  tx_buf; int /*<<< orphan*/  cmdlock; int /*<<< orphan*/  command; struct tinydrm_device tinydrm; } ;
struct drm_simple_display_pipe_funcs {int dummy; } ;
struct drm_driver {int dummy; } ;
struct drm_display_mode {int vdisplay; int hdisplay; } ;
struct device {int dummy; } ;
struct TYPE_3__ {int preferred_depth; } ;
struct TYPE_4__ {TYPE_1__ mode_config; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,int,unsigned int) ; 
 int /*<<< orphan*/  DRM_MODE_CONNECTOR_VIRTUAL ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  devm_kmalloc (struct device*,size_t,int /*<<< orphan*/ ) ; 
 int devm_tinydrm_init (struct device*,struct tinydrm_device*,int /*<<< orphan*/ *,struct drm_driver*) ; 
 int /*<<< orphan*/  drm_mode_config_reset (TYPE_2__*) ; 
 int /*<<< orphan*/  mipi_dbi_fb_dirty ; 
 int /*<<< orphan*/  mipi_dbi_fb_funcs ; 
 int /*<<< orphan*/  mipi_dbi_formats ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int tinydrm_display_pipe_init (struct tinydrm_device*,struct drm_simple_display_pipe_funcs const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct drm_display_mode const*,unsigned int) ; 

int mipi_dbi_init(struct device *dev, struct mipi_dbi *mipi,
		  const struct drm_simple_display_pipe_funcs *pipe_funcs,
		  struct drm_driver *driver,
		  const struct drm_display_mode *mode, unsigned int rotation)
{
	size_t bufsize = mode->vdisplay * mode->hdisplay * sizeof(u16);
	struct tinydrm_device *tdev = &mipi->tinydrm;
	int ret;

	if (!mipi->command)
		return -EINVAL;

	mutex_init(&mipi->cmdlock);

	mipi->tx_buf = devm_kmalloc(dev, bufsize, GFP_KERNEL);
	if (!mipi->tx_buf)
		return -ENOMEM;

	ret = devm_tinydrm_init(dev, tdev, &mipi_dbi_fb_funcs, driver);
	if (ret)
		return ret;

	tdev->fb_dirty = mipi_dbi_fb_dirty;

	/* TODO: Maybe add DRM_MODE_CONNECTOR_SPI */
	ret = tinydrm_display_pipe_init(tdev, pipe_funcs,
					DRM_MODE_CONNECTOR_VIRTUAL,
					mipi_dbi_formats,
					ARRAY_SIZE(mipi_dbi_formats), mode,
					rotation);
	if (ret)
		return ret;

	tdev->drm->mode_config.preferred_depth = 16;
	mipi->rotation = rotation;

	drm_mode_config_reset(tdev->drm);

	DRM_DEBUG_KMS("preferred_depth=%u, rotation = %u\n",
		      tdev->drm->mode_config.preferred_depth, rotation);

	return 0;
}