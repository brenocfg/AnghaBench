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
struct mdev_link {int create_link; int /*<<< orphan*/  list; } ;
struct config_item {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int ENODEV ; 
 int kstrtobool (char const*,int*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mdev_link_list ; 
 int set_config_and_add_link (struct mdev_link*) ; 
 struct mdev_link* to_mdev_link (struct config_item*) ; 

__attribute__((used)) static ssize_t mdev_link_create_link_store(struct config_item *item,
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
	ret = set_config_and_add_link(mdev_link);
	if (ret && ret != -ENODEV)
		return ret;
	list_add_tail(&mdev_link->list, &mdev_link_list);
	mdev_link->create_link = tmp;
	return count;
}