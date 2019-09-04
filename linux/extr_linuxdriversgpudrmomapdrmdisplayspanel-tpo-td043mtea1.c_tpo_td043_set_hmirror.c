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
struct panel_drv_data {int hmirror; int /*<<< orphan*/  vmirror; int /*<<< orphan*/  spi; } ;
struct omap_dss_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 struct panel_drv_data* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int tpo_td043_write_mirror (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tpo_td043_set_hmirror(struct omap_dss_device *dssdev, bool enable)
{
	struct panel_drv_data *ddata = dev_get_drvdata(dssdev->dev);

	ddata->hmirror = enable;
	return tpo_td043_write_mirror(ddata->spi, ddata->hmirror,
			ddata->vmirror);
}