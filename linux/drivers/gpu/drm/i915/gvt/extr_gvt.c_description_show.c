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
struct intel_vgpu_type {int fence; int weight; int /*<<< orphan*/  resolution; int /*<<< orphan*/  high_gm_size; int /*<<< orphan*/  low_gm_size; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_2__ {void* gvt; } ;

/* Variables and functions */
 int BYTES_TO_MB (int /*<<< orphan*/ ) ; 
 struct intel_vgpu_type* intel_gvt_find_vgpu_type (void*,int /*<<< orphan*/ ) ; 
 TYPE_1__* kdev_to_i915 (struct device*) ; 
 int /*<<< orphan*/  kobject_name (struct kobject*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int,int,int,char*,int) ; 
 char* vgpu_edid_str (int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t description_show(struct kobject *kobj, struct device *dev,
		char *buf)
{
	struct intel_vgpu_type *type;
	void *gvt = kdev_to_i915(dev)->gvt;

	type = intel_gvt_find_vgpu_type(gvt, kobject_name(kobj));
	if (!type)
		return 0;

	return sprintf(buf, "low_gm_size: %dMB\nhigh_gm_size: %dMB\n"
		       "fence: %d\nresolution: %s\n"
		       "weight: %d\n",
		       BYTES_TO_MB(type->low_gm_size),
		       BYTES_TO_MB(type->high_gm_size),
		       type->fence, vgpu_edid_str(type->resolution),
		       type->weight);
}