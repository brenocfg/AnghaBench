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
struct tinydrm_device {int dummy; } ;
struct mipi_dbi {int enabled; scalar_t__ regulator; scalar_t__ backlight; } ;
struct drm_simple_display_pipe {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*) ; 
 int /*<<< orphan*/  backlight_disable (scalar_t__) ; 
 int /*<<< orphan*/  mipi_dbi_blank (struct mipi_dbi*) ; 
 struct mipi_dbi* mipi_dbi_from_tinydrm (struct tinydrm_device*) ; 
 struct tinydrm_device* pipe_to_tinydrm (struct drm_simple_display_pipe*) ; 
 int /*<<< orphan*/  regulator_disable (scalar_t__) ; 

void mipi_dbi_pipe_disable(struct drm_simple_display_pipe *pipe)
{
	struct tinydrm_device *tdev = pipe_to_tinydrm(pipe);
	struct mipi_dbi *mipi = mipi_dbi_from_tinydrm(tdev);

	DRM_DEBUG_KMS("\n");

	mipi->enabled = false;

	if (mipi->backlight)
		backlight_disable(mipi->backlight);
	else
		mipi_dbi_blank(mipi);

	if (mipi->regulator)
		regulator_disable(mipi->regulator);
}