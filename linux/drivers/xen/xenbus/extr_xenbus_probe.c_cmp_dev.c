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
struct xenbus_device {int /*<<< orphan*/  nodename; } ;
struct xb_find_info {struct xenbus_device* dev; int /*<<< orphan*/  nodename; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  get_device (struct device*) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct xenbus_device* to_xenbus_device (struct device*) ; 

__attribute__((used)) static int cmp_dev(struct device *dev, void *data)
{
	struct xenbus_device *xendev = to_xenbus_device(dev);
	struct xb_find_info *info = data;

	if (!strcmp(xendev->nodename, info->nodename)) {
		info->dev = xendev;
		get_device(dev);
		return 1;
	}
	return 0;
}