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
struct mdev_link {int destroy_link; int /*<<< orphan*/  list; int /*<<< orphan*/  comp; int /*<<< orphan*/  channel; int /*<<< orphan*/  device; } ;
struct config_item {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int kstrtobool (char const*,int*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mdev_link_list ; 
 int most_remove_link (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct mdev_link* to_mdev_link (struct config_item*) ; 

__attribute__((used)) static ssize_t mdev_link_destroy_link_store(struct config_item *item,
					    const char *page, size_t count)
{
	struct mdev_link *mdev_link = to_mdev_link(item);
	bool tmp;
	int ret;

	ret = kstrtobool(page, &tmp);
	if (ret)
		return ret;
	if (!tmp)
		return count;
	mdev_link->destroy_link = tmp;
	ret = most_remove_link(mdev_link->device, mdev_link->channel,
			       mdev_link->comp);
	if (ret)
		return ret;
	if (!list_empty(&mdev_link_list))
		list_del(&mdev_link->list);
	return count;
}