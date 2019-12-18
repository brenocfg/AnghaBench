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
struct td043mtea1_panel {int /*<<< orphan*/  panel; } ;
struct TYPE_2__ {int /*<<< orphan*/  kobj; } ;
struct spi_device {TYPE_1__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_panel_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_panel_remove (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_panel_unprepare (int /*<<< orphan*/ *) ; 
 struct td043mtea1_panel* spi_get_drvdata (struct spi_device*) ; 
 int /*<<< orphan*/  sysfs_remove_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  td043mtea1_attr_group ; 

__attribute__((used)) static int td043mtea1_remove(struct spi_device *spi)
{
	struct td043mtea1_panel *lcd = spi_get_drvdata(spi);

	drm_panel_remove(&lcd->panel);
	drm_panel_disable(&lcd->panel);
	drm_panel_unprepare(&lcd->panel);

	sysfs_remove_group(&spi->dev.kobj, &td043mtea1_attr_group);

	return 0;
}