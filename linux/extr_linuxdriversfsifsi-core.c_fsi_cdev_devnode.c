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
typedef  int /*<<< orphan*/  umode_t ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  kuid_t ;
typedef  int /*<<< orphan*/  kgid_t ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_name (struct device*) ; 
 char* kasprintf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static char *fsi_cdev_devnode(struct device *dev, umode_t *mode,
			      kuid_t *uid, kgid_t *gid)
{
#ifdef CONFIG_FSI_NEW_DEV_NODE
	return kasprintf(GFP_KERNEL, "fsi/%s", dev_name(dev));
#else
	return kasprintf(GFP_KERNEL, "%s", dev_name(dev));
#endif
}