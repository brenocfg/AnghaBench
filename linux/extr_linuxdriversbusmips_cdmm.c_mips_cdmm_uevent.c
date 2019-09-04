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
struct mips_cdmm_device {int /*<<< orphan*/  type; int /*<<< orphan*/  rev; int /*<<< orphan*/  cpu; } ;
struct kobj_uevent_env {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int add_uevent_var (struct kobj_uevent_env*,char*,int /*<<< orphan*/ ) ; 
 struct mips_cdmm_device* to_mips_cdmm_device (struct device*) ; 

__attribute__((used)) static int mips_cdmm_uevent(struct device *dev, struct kobj_uevent_env *env)
{
	struct mips_cdmm_device *cdev = to_mips_cdmm_device(dev);
	int retval = 0;

	retval = add_uevent_var(env, "CDMM_CPU=%u", cdev->cpu);
	if (retval)
		return retval;

	retval = add_uevent_var(env, "CDMM_TYPE=0x%02x", cdev->type);
	if (retval)
		return retval;

	retval = add_uevent_var(env, "CDMM_REV=%u", cdev->rev);
	if (retval)
		return retval;

	retval = add_uevent_var(env, "MODALIAS=mipscdmm:t%02X", cdev->type);
	return retval;
}