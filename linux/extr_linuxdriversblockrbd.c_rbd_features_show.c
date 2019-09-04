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
struct TYPE_2__ {scalar_t__ features; } ;
struct rbd_device {TYPE_1__ mapping; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 struct rbd_device* dev_to_rbd_dev (struct device*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,unsigned long long) ; 

__attribute__((used)) static ssize_t rbd_features_show(struct device *dev,
			     struct device_attribute *attr, char *buf)
{
	struct rbd_device *rbd_dev = dev_to_rbd_dev(dev);

	return sprintf(buf, "0x%016llx\n",
			(unsigned long long)rbd_dev->mapping.features);
}