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
struct xenbus_device {int /*<<< orphan*/  nodename; } ;
struct xen_blkif {int domid; TYPE_1__* be; } ;
struct TYPE_2__ {struct xenbus_device* dev; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (char*) ; 
 int PTR_ERR (char*) ; 
 int /*<<< orphan*/  TASK_COMM_LEN ; 
 int /*<<< orphan*/  XBT_NIL ; 
 int /*<<< orphan*/  kfree (char*) ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,int,char*) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 char* strstr (char*,char*) ; 
 char* xenbus_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int blkback_name(struct xen_blkif *blkif, char *buf)
{
	char *devpath, *devname;
	struct xenbus_device *dev = blkif->be->dev;

	devpath = xenbus_read(XBT_NIL, dev->nodename, "dev", NULL);
	if (IS_ERR(devpath))
		return PTR_ERR(devpath);

	devname = strstr(devpath, "/dev/");
	if (devname != NULL)
		devname += strlen("/dev/");
	else
		devname  = devpath;

	snprintf(buf, TASK_COMM_LEN, "%d.%s", blkif->domid, devname);
	kfree(devpath);

	return 0;
}