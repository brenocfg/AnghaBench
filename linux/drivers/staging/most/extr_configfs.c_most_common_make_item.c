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
struct config_item {int dummy; } ;
struct mdev_link {struct config_item item; int /*<<< orphan*/  name; int /*<<< orphan*/  comp; } ;
struct TYPE_2__ {int /*<<< orphan*/  ci_namebuf; } ;
struct config_group {TYPE_1__ cg_item; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct config_item* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  config_item_init_type_name (struct config_item*,char const*,int /*<<< orphan*/ *) ; 
 struct mdev_link* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mdev_link_type ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static struct config_item *most_common_make_item(struct config_group *group,
						 const char *name)
{
	struct mdev_link *mdev_link;

	mdev_link = kzalloc(sizeof(*mdev_link), GFP_KERNEL);
	if (!mdev_link)
		return ERR_PTR(-ENOMEM);

	config_item_init_type_name(&mdev_link->item, name,
				   &mdev_link_type);

	if (!strcmp(group->cg_item.ci_namebuf, "most_cdev"))
		strcpy(mdev_link->comp, "cdev");
	else if (!strcmp(group->cg_item.ci_namebuf, "most_net"))
		strcpy(mdev_link->comp, "net");
	else if (!strcmp(group->cg_item.ci_namebuf, "most_video"))
		strcpy(mdev_link->comp, "video");
	strcpy(mdev_link->name, name);
	return &mdev_link->item;
}