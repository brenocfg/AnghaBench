#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_2__* funcs; } ;
struct TYPE_8__ {TYPE_1__* funcs; } ;
struct dw_mipi_dsi {int /*<<< orphan*/  pllref_clk; TYPE_3__ encoder; TYPE_4__ connector; int /*<<< orphan*/  dsi_host; } ;
struct device {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* destroy ) (TYPE_3__*) ;} ;
struct TYPE_5__ {int /*<<< orphan*/  (* destroy ) (TYPE_4__*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 struct dw_mipi_dsi* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  mipi_dsi_host_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_disable (struct device*) ; 
 int /*<<< orphan*/  stub1 (TYPE_4__*) ; 
 int /*<<< orphan*/  stub2 (TYPE_3__*) ; 

__attribute__((used)) static void dw_mipi_dsi_unbind(struct device *dev, struct device *master,
			       void *data)
{
	struct dw_mipi_dsi *dsi = dev_get_drvdata(dev);

	mipi_dsi_host_unregister(&dsi->dsi_host);
	pm_runtime_disable(dev);

	dsi->connector.funcs->destroy(&dsi->connector);
	dsi->encoder.funcs->destroy(&dsi->encoder);

	clk_disable_unprepare(dsi->pllref_clk);
}