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
struct mipi_dbi {int enabled; } ;
struct drm_simple_display_pipe {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*) ; 
 int /*<<< orphan*/  ILI9225_DISPLAY_CONTROL_1 ; 
 int /*<<< orphan*/  ILI9225_POWER_CONTROL_1 ; 
 int /*<<< orphan*/  ILI9225_POWER_CONTROL_2 ; 
 int /*<<< orphan*/  ili9225_command (struct mipi_dbi*,int /*<<< orphan*/ ,int) ; 
 struct mipi_dbi* mipi_dbi_from_tinydrm (struct tinydrm_device*) ; 
 int /*<<< orphan*/  msleep (int) ; 
 struct tinydrm_device* pipe_to_tinydrm (struct drm_simple_display_pipe*) ; 

__attribute__((used)) static void ili9225_pipe_disable(struct drm_simple_display_pipe *pipe)
{
	struct tinydrm_device *tdev = pipe_to_tinydrm(pipe);
	struct mipi_dbi *mipi = mipi_dbi_from_tinydrm(tdev);

	DRM_DEBUG_KMS("\n");

	if (!mipi->enabled)
		return;

	ili9225_command(mipi, ILI9225_DISPLAY_CONTROL_1, 0x0000);
	msleep(50);
	ili9225_command(mipi, ILI9225_POWER_CONTROL_2, 0x0007);
	msleep(50);
	ili9225_command(mipi, ILI9225_POWER_CONTROL_1, 0x0a02);

	mipi->enabled = false;
}