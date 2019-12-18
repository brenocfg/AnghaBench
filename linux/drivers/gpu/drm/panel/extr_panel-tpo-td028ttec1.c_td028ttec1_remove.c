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
struct td028ttec1_panel {int /*<<< orphan*/  panel; } ;
struct spi_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_panel_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_panel_remove (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_panel_unprepare (int /*<<< orphan*/ *) ; 
 struct td028ttec1_panel* spi_get_drvdata (struct spi_device*) ; 

__attribute__((used)) static int td028ttec1_remove(struct spi_device *spi)
{
	struct td028ttec1_panel *lcd = spi_get_drvdata(spi);

	drm_panel_remove(&lcd->panel);
	drm_panel_disable(&lcd->panel);
	drm_panel_unprepare(&lcd->panel);

	return 0;
}