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
struct uvcg_control_class_group {char* name; int /*<<< orphan*/  group; } ;
struct config_group {int dummy; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (char const* const*) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  config_group_init_type_name (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  configfs_add_default_group (int /*<<< orphan*/ *,struct config_group*) ; 
 struct uvcg_control_class_group* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uvcg_control_class_type ; 

__attribute__((used)) static int uvcg_control_class_create_children(struct config_group *parent)
{
	static const char * const names[] = { "fs", "ss" };
	unsigned int i;

	for (i = 0; i < ARRAY_SIZE(names); ++i) {
		struct uvcg_control_class_group *group;

		group = kzalloc(sizeof(*group), GFP_KERNEL);
		if (!group)
			return -ENOMEM;

		group->name = names[i];

		config_group_init_type_name(&group->group, group->name,
					    &uvcg_control_class_type);
		configfs_add_default_group(&group->group, parent);
	}

	return 0;
}