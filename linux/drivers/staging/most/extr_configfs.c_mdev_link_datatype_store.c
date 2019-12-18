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
struct mdev_link {int /*<<< orphan*/  datatype; } ;
struct config_item {int dummy; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 size_t EINVAL ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  sysfs_streq (char const*,char*) ; 
 struct mdev_link* to_mdev_link (struct config_item*) ; 

__attribute__((used)) static ssize_t mdev_link_datatype_store(struct config_item *item,
					const char *page, size_t count)
{
	struct mdev_link *mdev_link = to_mdev_link(item);

	if (!sysfs_streq(page, "control") && !sysfs_streq(page, "async") &&
	    !sysfs_streq(page, "sync") && !sysfs_streq(page, "isoc") &&
	    !sysfs_streq(page, "isoc_avp"))
		return -EINVAL;
	strcpy(mdev_link->datatype, page);
	return count;
}