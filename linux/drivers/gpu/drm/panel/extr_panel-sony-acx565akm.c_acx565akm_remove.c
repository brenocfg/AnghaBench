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
struct spi_device {int dummy; } ;
struct acx565akm_panel {int /*<<< orphan*/  panel; scalar_t__ has_bc; } ;

/* Variables and functions */
 int /*<<< orphan*/  acx565akm_backlight_cleanup (struct acx565akm_panel*) ; 
 int /*<<< orphan*/  drm_panel_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_panel_remove (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_panel_unprepare (int /*<<< orphan*/ *) ; 
 struct acx565akm_panel* spi_get_drvdata (struct spi_device*) ; 

__attribute__((used)) static int acx565akm_remove(struct spi_device *spi)
{
	struct acx565akm_panel *lcd = spi_get_drvdata(spi);

	drm_panel_remove(&lcd->panel);

	if (lcd->has_bc)
		acx565akm_backlight_cleanup(lcd);

	drm_panel_disable(&lcd->panel);
	drm_panel_unprepare(&lcd->panel);

	return 0;
}