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
struct panel_drv_data {int /*<<< orphan*/ * src; int /*<<< orphan*/  channel; } ;
struct omap_dss_device {TYPE_2__* ops; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* release_vc ) (struct omap_dss_device*,int /*<<< orphan*/ ) ;} ;
struct TYPE_4__ {TYPE_1__ dsi; } ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct omap_dss_device*,int /*<<< orphan*/ ) ; 
 struct panel_drv_data* to_panel_data (struct omap_dss_device*) ; 

__attribute__((used)) static void dsicm_disconnect(struct omap_dss_device *src,
			     struct omap_dss_device *dst)
{
	struct panel_drv_data *ddata = to_panel_data(dst);

	src->ops->dsi.release_vc(src, ddata->channel);
	ddata->src = NULL;
}