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
struct videomode {scalar_t__ pixelclock; } ;
struct sdi_device {TYPE_1__* dss; } ;
struct omap_dss_device {int dispc_channel; } ;
typedef  enum omap_channel { ____Placeholder_omap_channel } omap_channel ;
struct TYPE_2__ {int /*<<< orphan*/  dispc; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  dispc_mgr_timings_ok (int /*<<< orphan*/ ,int,struct videomode*) ; 
 struct sdi_device* dssdev_to_sdi (struct omap_dss_device*) ; 

__attribute__((used)) static int sdi_check_timings(struct omap_dss_device *dssdev,
			     struct videomode *vm)
{
	struct sdi_device *sdi = dssdev_to_sdi(dssdev);
	enum omap_channel channel = dssdev->dispc_channel;

	if (!dispc_mgr_timings_ok(sdi->dss->dispc, channel, vm))
		return -EINVAL;

	if (vm->pixelclock == 0)
		return -EINVAL;

	return 0;
}