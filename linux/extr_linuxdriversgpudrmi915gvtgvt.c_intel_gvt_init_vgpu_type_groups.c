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
struct intel_vgpu_type {int /*<<< orphan*/  name; } ;
struct intel_gvt {int num_types; struct intel_vgpu_type* types; } ;
struct attribute_group {int /*<<< orphan*/  attrs; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  gvt_type_attrs ; 
 struct attribute_group** gvt_vgpu_type_groups ; 
 int /*<<< orphan*/  kfree (struct attribute_group*) ; 
 struct attribute_group* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool intel_gvt_init_vgpu_type_groups(struct intel_gvt *gvt)
{
	int i, j;
	struct intel_vgpu_type *type;
	struct attribute_group *group;

	for (i = 0; i < gvt->num_types; i++) {
		type = &gvt->types[i];

		group = kzalloc(sizeof(struct attribute_group), GFP_KERNEL);
		if (WARN_ON(!group))
			goto unwind;

		group->name = type->name;
		group->attrs = gvt_type_attrs;
		gvt_vgpu_type_groups[i] = group;
	}

	return true;

unwind:
	for (j = 0; j < i; j++) {
		group = gvt_vgpu_type_groups[j];
		kfree(group);
	}

	return false;
}