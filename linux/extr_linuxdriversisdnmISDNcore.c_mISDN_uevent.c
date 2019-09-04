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
struct mISDNdevice {int /*<<< orphan*/  nrbchan; } ;
struct kobj_uevent_env {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 scalar_t__ add_uevent_var (struct kobj_uevent_env*,char*,int /*<<< orphan*/ ) ; 
 struct mISDNdevice* dev_to_mISDN (struct device*) ; 

__attribute__((used)) static int mISDN_uevent(struct device *dev, struct kobj_uevent_env *env)
{
	struct mISDNdevice *mdev = dev_to_mISDN(dev);

	if (!mdev)
		return 0;

	if (add_uevent_var(env, "nchans=%d", mdev->nrbchan))
		return -ENOMEM;

	return 0;
}