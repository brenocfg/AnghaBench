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
struct TYPE_3__ {int preferred_depth; } ;
struct TYPE_4__ {TYPE_1__ mode_config; } ;
struct mipi_dbi_dev {TYPE_2__ drm; } ;
struct drm_simple_display_pipe_funcs {int dummy; } ;
struct drm_display_mode {int vdisplay; int hdisplay; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int mipi_dbi_dev_init_with_formats (struct mipi_dbi_dev*,struct drm_simple_display_pipe_funcs const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct drm_display_mode const*,unsigned int,size_t) ; 
 int /*<<< orphan*/  mipi_dbi_formats ; 

int mipi_dbi_dev_init(struct mipi_dbi_dev *dbidev,
		      const struct drm_simple_display_pipe_funcs *funcs,
		      const struct drm_display_mode *mode, unsigned int rotation)
{
	size_t bufsize = mode->vdisplay * mode->hdisplay * sizeof(u16);

	dbidev->drm.mode_config.preferred_depth = 16;

	return mipi_dbi_dev_init_with_formats(dbidev, funcs, mipi_dbi_formats,
					      ARRAY_SIZE(mipi_dbi_formats), mode,
					      rotation, bufsize);
}