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
struct rio_dev {int /*<<< orphan*/  asm_did; int /*<<< orphan*/  asm_vid; int /*<<< orphan*/  did; int /*<<< orphan*/  vid; } ;
struct kobj_uevent_env {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 scalar_t__ add_uevent_var (struct kobj_uevent_env*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct rio_dev* to_rio_dev (struct device*) ; 

__attribute__((used)) static int rio_uevent(struct device *dev, struct kobj_uevent_env *env)
{
	struct rio_dev *rdev;

	if (!dev)
		return -ENODEV;

	rdev = to_rio_dev(dev);
	if (!rdev)
		return -ENODEV;

	if (add_uevent_var(env, "MODALIAS=rapidio:v%04Xd%04Xav%04Xad%04X",
			   rdev->vid, rdev->did, rdev->asm_vid, rdev->asm_did))
		return -ENOMEM;
	return 0;
}