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
struct venc_device {int /*<<< orphan*/  debugfs; } ;
struct device {int dummy; } ;

/* Variables and functions */
 struct venc_device* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  dss_debugfs_remove_file (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void venc_unbind(struct device *dev, struct device *master, void *data)
{
	struct venc_device *venc = dev_get_drvdata(dev);

	dss_debugfs_remove_file(venc->debugfs);
}