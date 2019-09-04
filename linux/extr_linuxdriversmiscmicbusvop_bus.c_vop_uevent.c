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
struct TYPE_2__ {int /*<<< orphan*/  vendor; int /*<<< orphan*/  device; } ;
struct vop_device {TYPE_1__ id; } ;
struct kobj_uevent_env {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int add_uevent_var (struct kobj_uevent_env*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct vop_device* dev_to_vop (struct device*) ; 

__attribute__((used)) static int vop_uevent(struct device *dv, struct kobj_uevent_env *env)
{
	struct vop_device *dev = dev_to_vop(dv);

	return add_uevent_var(env, "MODALIAS=vop:d%08Xv%08X",
			      dev->id.device, dev->id.vendor);
}