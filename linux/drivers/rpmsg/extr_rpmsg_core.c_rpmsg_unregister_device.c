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
struct rpmsg_channel_info {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  device_unregister (struct device*) ; 
 int /*<<< orphan*/  put_device (struct device*) ; 
 struct device* rpmsg_find_device (struct device*,struct rpmsg_channel_info*) ; 

int rpmsg_unregister_device(struct device *parent,
			    struct rpmsg_channel_info *chinfo)
{
	struct device *dev;

	dev = rpmsg_find_device(parent, chinfo);
	if (!dev)
		return -EINVAL;

	device_unregister(dev);

	put_device(dev);

	return 0;
}