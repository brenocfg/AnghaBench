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
struct omap_dss_device {int /*<<< orphan*/  owner; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/ * get_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  try_module_get (int /*<<< orphan*/ ) ; 

struct omap_dss_device *omap_dss_get_device(struct omap_dss_device *dssdev)
{
	if (!try_module_get(dssdev->owner))
		return NULL;

	if (get_device(dssdev->dev) == NULL) {
		module_put(dssdev->owner);
		return NULL;
	}

	return dssdev;
}