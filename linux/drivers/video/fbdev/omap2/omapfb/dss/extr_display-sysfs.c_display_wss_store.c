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
typedef  int u32 ;
struct omap_dss_device {TYPE_1__* driver; } ;
typedef  int ssize_t ;
struct TYPE_2__ {int (* set_wss ) (struct omap_dss_device*,int) ;int /*<<< orphan*/  get_wss; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOENT ; 
 int kstrtou32 (char const*,int /*<<< orphan*/ ,int*) ; 
 int stub1 (struct omap_dss_device*,int) ; 

__attribute__((used)) static ssize_t display_wss_store(struct omap_dss_device *dssdev,
	const char *buf, size_t size)
{
	u32 wss;
	int r;

	if (!dssdev->driver->get_wss || !dssdev->driver->set_wss)
		return -ENOENT;

	r = kstrtou32(buf, 0, &wss);
	if (r)
		return r;

	if (wss > 0xfffff)
		return -EINVAL;

	r = dssdev->driver->set_wss(dssdev, wss);
	if (r)
		return r;

	return size;
}