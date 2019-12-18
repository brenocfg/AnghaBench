#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct mdev_device {int dummy; } ;
struct TYPE_4__ {TYPE_3__** shadow; } ;
struct intel_vgpu {TYPE_1__ submission; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_6__ {TYPE_2__* gem_context; } ;
struct TYPE_5__ {int hw_id; } ;

/* Variables and functions */
 struct mdev_device* mdev_from_dev (struct device*) ; 
 scalar_t__ mdev_get_drvdata (struct mdev_device*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,...) ; 

__attribute__((used)) static ssize_t
hw_id_show(struct device *dev, struct device_attribute *attr,
	   char *buf)
{
	struct mdev_device *mdev = mdev_from_dev(dev);

	if (mdev) {
		struct intel_vgpu *vgpu = (struct intel_vgpu *)
			mdev_get_drvdata(mdev);
		return sprintf(buf, "%u\n",
			       vgpu->submission.shadow[0]->gem_context->hw_id);
	}
	return sprintf(buf, "\n");
}