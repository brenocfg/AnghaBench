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
struct config_item {int dummy; } ;
struct mdev_link {struct config_item item; int /*<<< orphan*/  comp; int /*<<< orphan*/  name; scalar_t__ create_link; } ;
struct config_group {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct config_item* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  config_item_init_type_name (struct config_item*,char const*,int /*<<< orphan*/ *) ; 
 struct mdev_link* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mdev_link_type ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static struct config_item *most_snd_grp_make_item(struct config_group *group,
						  const char *name)
{
	struct mdev_link *mdev_link;

	mdev_link = kzalloc(sizeof(*mdev_link), GFP_KERNEL);
	if (!mdev_link)
		return ERR_PTR(-ENOMEM);

	config_item_init_type_name(&mdev_link->item, name, &mdev_link_type);
	mdev_link->create_link = 0;
	strcpy(mdev_link->name, name);
	strcpy(mdev_link->comp, "sound");
	return &mdev_link->item;
}