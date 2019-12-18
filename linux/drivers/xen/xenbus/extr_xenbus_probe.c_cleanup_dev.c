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
struct xenbus_device {char* nodename; } ;
struct xb_find_info {char* nodename; struct xenbus_device* dev; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTK (char*,char*) ; 
 int /*<<< orphan*/  get_device (struct device*) ; 
 int strlen (char*) ; 
 scalar_t__ strncmp (char*,char*,int) ; 
 struct xenbus_device* to_xenbus_device (struct device*) ; 

__attribute__((used)) static int cleanup_dev(struct device *dev, void *data)
{
	struct xenbus_device *xendev = to_xenbus_device(dev);
	struct xb_find_info *info = data;
	int len = strlen(info->nodename);

	DPRINTK("%s", info->nodename);

	/* Match the info->nodename path, or any subdirectory of that path. */
	if (strncmp(xendev->nodename, info->nodename, len))
		return 0;

	/* If the node name is longer, ensure it really is a subdirectory. */
	if ((strlen(xendev->nodename) > len) && (xendev->nodename[len] != '/'))
		return 0;

	info->dev = xendev;
	get_device(dev);
	return 1;
}