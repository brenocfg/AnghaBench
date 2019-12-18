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
struct mdev_link {int /*<<< orphan*/  list; int /*<<< orphan*/  comp; int /*<<< orphan*/  channel; int /*<<< orphan*/  device; } ;
struct config_item {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  kfree (struct mdev_link*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mdev_link_list ; 
 int most_remove_link (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 struct mdev_link* to_mdev_link (struct config_item*) ; 

__attribute__((used)) static void mdev_link_release(struct config_item *item)
{
	struct mdev_link *mdev_link = to_mdev_link(item);
	int ret;

	if (!list_empty(&mdev_link_list)) {
		ret = most_remove_link(mdev_link->device, mdev_link->channel,
				       mdev_link->comp);
		if (ret && (ret != -ENODEV))
			pr_err("Removing link failed.\n");
		list_del(&mdev_link->list);
	}
	kfree(to_mdev_link(item));
}