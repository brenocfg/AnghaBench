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
typedef  int /*<<< orphan*/  uint32_t ;
struct tcmu_dev {int /*<<< orphan*/  cmdr_lock; int /*<<< orphan*/  name; } ;
struct page {int dummy; } ;

/* Variables and functions */
 scalar_t__ likely (struct page*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct page* tcmu_get_block_page (struct tcmu_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct page *tcmu_try_get_block_page(struct tcmu_dev *udev, uint32_t dbi)
{
	struct page *page;

	mutex_lock(&udev->cmdr_lock);
	page = tcmu_get_block_page(udev, dbi);
	if (likely(page)) {
		mutex_unlock(&udev->cmdr_lock);
		return page;
	}

	/*
	 * Userspace messed up and passed in a address not in the
	 * data iov passed to it.
	 */
	pr_err("Invalid addr to data block mapping  (dbi %u) on device %s\n",
	       dbi, udev->name);
	page = NULL;
	mutex_unlock(&udev->cmdr_lock);

	return page;
}