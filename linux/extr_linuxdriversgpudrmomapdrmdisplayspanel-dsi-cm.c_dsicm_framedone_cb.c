#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct panel_drv_data {struct omap_dss_device* in; TYPE_1__* pdev; } ;
struct TYPE_6__ {TYPE_2__* dsi; } ;
struct omap_dss_device {TYPE_3__ ops; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* bus_unlock ) (struct omap_dss_device*) ;} ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  stub1 (struct omap_dss_device*) ; 

__attribute__((used)) static void dsicm_framedone_cb(int err, void *data)
{
	struct panel_drv_data *ddata = data;
	struct omap_dss_device *in = ddata->in;

	dev_dbg(&ddata->pdev->dev, "framedone, err %d\n", err);
	in->ops.dsi->bus_unlock(ddata->in);
}