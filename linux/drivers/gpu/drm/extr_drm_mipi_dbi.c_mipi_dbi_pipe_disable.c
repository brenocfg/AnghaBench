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
struct mipi_dbi_dev {int enabled; scalar_t__ regulator; scalar_t__ backlight; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;
struct drm_simple_display_pipe {TYPE_1__ crtc; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*) ; 
 int /*<<< orphan*/  backlight_disable (scalar_t__) ; 
 struct mipi_dbi_dev* drm_to_mipi_dbi_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mipi_dbi_blank (struct mipi_dbi_dev*) ; 
 int /*<<< orphan*/  regulator_disable (scalar_t__) ; 

void mipi_dbi_pipe_disable(struct drm_simple_display_pipe *pipe)
{
	struct mipi_dbi_dev *dbidev = drm_to_mipi_dbi_dev(pipe->crtc.dev);

	if (!dbidev->enabled)
		return;

	DRM_DEBUG_KMS("\n");

	dbidev->enabled = false;

	if (dbidev->backlight)
		backlight_disable(dbidev->backlight);
	else
		mipi_dbi_blank(dbidev);

	if (dbidev->regulator)
		regulator_disable(dbidev->regulator);
}