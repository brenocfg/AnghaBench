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
struct kobj_uevent_env {int dummy; } ;
struct ipack_device {int /*<<< orphan*/  id_device; int /*<<< orphan*/  id_vendor; int /*<<< orphan*/  id_format; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 scalar_t__ add_uevent_var (struct kobj_uevent_env*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ipack_device* to_ipack_dev (struct device*) ; 

__attribute__((used)) static int ipack_uevent(struct device *dev, struct kobj_uevent_env *env)
{
	struct ipack_device *idev;

	if (!dev)
		return -ENODEV;

	idev = to_ipack_dev(dev);

	if (add_uevent_var(env,
			   "MODALIAS=ipack:f%02Xv%08Xd%08X", idev->id_format,
			   idev->id_vendor, idev->id_device))
		return -ENOMEM;

	return 0;
}