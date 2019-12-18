#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct uvc_streaming {int intfnum; struct dentry* debugfs_dir; TYPE_2__* dev; } ;
struct usb_device {int devnum; TYPE_1__* bus; } ;
struct dentry {int dummy; } ;
typedef  int /*<<< orphan*/  dir_name ;
struct TYPE_4__ {struct usb_device* udev; } ;
struct TYPE_3__ {int busnum; } ;

/* Variables and functions */
 scalar_t__ IS_ERR_OR_NULL (struct dentry*) ; 
 int /*<<< orphan*/  KERN_INFO ; 
 struct dentry* debugfs_create_dir (char*,int /*<<< orphan*/ *) ; 
 struct dentry* debugfs_create_file (char*,int,struct dentry*,struct uvc_streaming*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int,int,int) ; 
 int /*<<< orphan*/  uvc_debugfs_cleanup_stream (struct uvc_streaming*) ; 
 int /*<<< orphan*/ * uvc_debugfs_root_dir ; 
 int /*<<< orphan*/  uvc_debugfs_stats_fops ; 
 int /*<<< orphan*/  uvc_printk (int /*<<< orphan*/ ,char*,...) ; 

void uvc_debugfs_init_stream(struct uvc_streaming *stream)
{
	struct usb_device *udev = stream->dev->udev;
	struct dentry *dent;
	char dir_name[33];

	if (uvc_debugfs_root_dir == NULL)
		return;

	snprintf(dir_name, sizeof(dir_name), "%u-%u-%u", udev->bus->busnum,
		 udev->devnum, stream->intfnum);

	dent = debugfs_create_dir(dir_name, uvc_debugfs_root_dir);
	if (IS_ERR_OR_NULL(dent)) {
		uvc_printk(KERN_INFO, "Unable to create debugfs %s "
			   "directory.\n", dir_name);
		return;
	}

	stream->debugfs_dir = dent;

	dent = debugfs_create_file("stats", 0444, stream->debugfs_dir,
				   stream, &uvc_debugfs_stats_fops);
	if (IS_ERR_OR_NULL(dent)) {
		uvc_printk(KERN_INFO, "Unable to create debugfs stats file.\n");
		uvc_debugfs_cleanup_stream(stream);
		return;
	}
}