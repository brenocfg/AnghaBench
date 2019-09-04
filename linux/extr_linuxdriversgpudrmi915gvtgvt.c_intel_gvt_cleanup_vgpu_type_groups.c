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
struct intel_gvt {int num_types; } ;
struct attribute_group {int dummy; } ;

/* Variables and functions */
 struct attribute_group** gvt_vgpu_type_groups ; 
 int /*<<< orphan*/  kfree (struct attribute_group*) ; 

__attribute__((used)) static void intel_gvt_cleanup_vgpu_type_groups(struct intel_gvt *gvt)
{
	int i;
	struct attribute_group *group;

	for (i = 0; i < gvt->num_types; i++) {
		group = gvt_vgpu_type_groups[i];
		gvt_vgpu_type_groups[i] = NULL;
		kfree(group);
	}
}