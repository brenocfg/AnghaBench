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
struct videomode {int dummy; } ;
struct TYPE_2__ {struct videomode vm; } ;
struct omap_dss_device {TYPE_1__ panel; } ;

/* Variables and functions */

__attribute__((used)) static void omapdss_default_get_timings(struct omap_dss_device *dssdev,
					struct videomode *vm)
{
	*vm = dssdev->panel.vm;
}