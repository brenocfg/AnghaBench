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
struct v4l2_capability {unsigned int device_caps; int capabilities; int /*<<< orphan*/  bus_info; int /*<<< orphan*/  card; int /*<<< orphan*/  driver; } ;
struct device {TYPE_1__* driver; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int V4L2_CAP_DEVICE_CAPS ; 
 char* dev_name (struct device*) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,char*) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void __fimc_vidioc_querycap(struct device *dev, struct v4l2_capability *cap,
						unsigned int caps)
{
	strlcpy(cap->driver, dev->driver->name, sizeof(cap->driver));
	strlcpy(cap->card, dev->driver->name, sizeof(cap->card));
	snprintf(cap->bus_info, sizeof(cap->bus_info),
				"platform:%s", dev_name(dev));
	cap->device_caps = caps;
	cap->capabilities = cap->device_caps | V4L2_CAP_DEVICE_CAPS;
}