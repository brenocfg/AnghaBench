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
struct sdi_device {int /*<<< orphan*/  vdds_sdi_reg; TYPE_1__* dss; int /*<<< orphan*/  output; } ;
struct omap_dss_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dispc; } ;

/* Variables and functions */
 int /*<<< orphan*/  dispc_runtime_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dss_mgr_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dss_sdi_disable (TYPE_1__*) ; 
 struct sdi_device* dssdev_to_sdi (struct omap_dss_device*) ; 
 int /*<<< orphan*/  regulator_disable (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sdi_display_disable(struct omap_dss_device *dssdev)
{
	struct sdi_device *sdi = dssdev_to_sdi(dssdev);

	dss_mgr_disable(&sdi->output);

	dss_sdi_disable(sdi->dss);

	dispc_runtime_put(sdi->dss->dispc);

	regulator_disable(sdi->vdds_sdi_reg);
}