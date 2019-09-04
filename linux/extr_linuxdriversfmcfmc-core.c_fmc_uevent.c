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
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  add_uevent_var (struct kobj_uevent_env*,char*,char*) ; 

__attribute__((used)) static int fmc_uevent(struct device *dev, struct kobj_uevent_env *env)
{
	/* struct fmc_device *fdev = to_fmc_device(dev); */

	/* FIXME: The MODALIAS */
	add_uevent_var(env, "MODALIAS=%s", "fmc");
	return 0;
}