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
struct omap_dss_device {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int sysfs_streq (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static int manager_display_match(struct omap_dss_device *dssdev, void *data)
{
	const char *str = data;

	return sysfs_streq(dssdev->name, str);
}