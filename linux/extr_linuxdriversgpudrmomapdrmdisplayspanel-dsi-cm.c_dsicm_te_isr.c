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
struct panel_drv_data {TYPE_1__* pdev; int /*<<< orphan*/  channel; int /*<<< orphan*/  te_timeout_work; int /*<<< orphan*/  do_update; struct omap_dss_device* in; } ;
struct TYPE_6__ {TYPE_2__* dsi; } ;
struct omap_dss_device {TYPE_3__ ops; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_5__ {int (* update ) (struct omap_dss_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct panel_drv_data*) ;int /*<<< orphan*/  (* bus_unlock ) (struct omap_dss_device*) ;} ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int atomic_cmpxchg (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cancel_delayed_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dsicm_framedone_cb ; 
 int stub1 (struct omap_dss_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct panel_drv_data*) ; 
 int /*<<< orphan*/  stub2 (struct omap_dss_device*) ; 

__attribute__((used)) static irqreturn_t dsicm_te_isr(int irq, void *data)
{
	struct panel_drv_data *ddata = data;
	struct omap_dss_device *in = ddata->in;
	int old;
	int r;

	old = atomic_cmpxchg(&ddata->do_update, 1, 0);

	if (old) {
		cancel_delayed_work(&ddata->te_timeout_work);

		r = in->ops.dsi->update(in, ddata->channel, dsicm_framedone_cb,
				ddata);
		if (r)
			goto err;
	}

	return IRQ_HANDLED;
err:
	dev_err(&ddata->pdev->dev, "start update failed\n");
	in->ops.dsi->bus_unlock(in);
	return IRQ_HANDLED;
}