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
struct uvcg_config_group_type {int (* create_children ) (struct config_group*) ;struct uvcg_config_group_type** children; } ;
struct config_group {int dummy; } ;

/* Variables and functions */
 int stub1 (struct config_group*) ; 
 int uvcg_config_create_group (struct config_group*,struct uvcg_config_group_type const*) ; 

__attribute__((used)) static int uvcg_config_create_children(struct config_group *group,
				const struct uvcg_config_group_type *type)
{
	const struct uvcg_config_group_type **child;
	int ret;

	if (type->create_children)
		return type->create_children(group);

	for (child = type->children; child && *child; ++child) {
		ret = uvcg_config_create_group(group, *child);
		if (ret < 0)
			return ret;
	}

	return 0;
}