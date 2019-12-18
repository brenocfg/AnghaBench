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
struct nt39016 {int /*<<< orphan*/  drm_panel; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_panel_remove (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nt39016_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nt39016_unprepare (int /*<<< orphan*/ *) ; 
 struct nt39016* spi_get_drvdata (struct spi_device*) ; 

__attribute__((used)) static int nt39016_remove(struct spi_device *spi)
{
	struct nt39016 *panel = spi_get_drvdata(spi);

	drm_panel_remove(&panel->drm_panel);

	nt39016_disable(&panel->drm_panel);
	nt39016_unprepare(&panel->drm_panel);

	return 0;
}