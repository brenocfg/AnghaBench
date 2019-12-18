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
struct uvcg_config_group_type {int /*<<< orphan*/  type; int /*<<< orphan*/  name; } ;
struct config_group {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  config_group_init_type_name (struct config_group*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  configfs_add_default_group (struct config_group*,struct config_group*) ; 
 struct config_group* kzalloc (int,int /*<<< orphan*/ ) ; 
 int uvcg_config_create_children (struct config_group*,struct uvcg_config_group_type const*) ; 

__attribute__((used)) static int uvcg_config_create_group(struct config_group *parent,
				    const struct uvcg_config_group_type *type)
{
	struct config_group *group;

	group = kzalloc(sizeof(*group), GFP_KERNEL);
	if (!group)
		return -ENOMEM;

	config_group_init_type_name(group, type->name, &type->type);
	configfs_add_default_group(group, parent);

	return uvcg_config_create_children(group, type);
}