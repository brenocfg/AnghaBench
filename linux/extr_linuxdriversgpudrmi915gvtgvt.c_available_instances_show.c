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
struct kobject {int dummy; } ;
struct intel_vgpu_type {unsigned int avail_instance; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_2__ {void* gvt; } ;

/* Variables and functions */
 struct intel_vgpu_type* intel_gvt_find_vgpu_type (void*,int /*<<< orphan*/ ) ; 
 TYPE_1__* kdev_to_i915 (struct device*) ; 
 int /*<<< orphan*/  kobject_name (struct kobject*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,unsigned int) ; 

__attribute__((used)) static ssize_t available_instances_show(struct kobject *kobj,
					struct device *dev, char *buf)
{
	struct intel_vgpu_type *type;
	unsigned int num = 0;
	void *gvt = kdev_to_i915(dev)->gvt;

	type = intel_gvt_find_vgpu_type(gvt, kobject_name(kobj));
	if (!type)
		num = 0;
	else
		num = type->avail_instance;

	return sprintf(buf, "%u\n", num);
}