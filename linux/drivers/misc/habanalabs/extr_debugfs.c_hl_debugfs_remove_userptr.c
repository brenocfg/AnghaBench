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
struct hl_userptr {int /*<<< orphan*/  debugfs_list; } ;
struct hl_dbg_device_entry {int /*<<< orphan*/  userptr_spinlock; } ;
struct hl_device {struct hl_dbg_device_entry hl_debugfs; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void hl_debugfs_remove_userptr(struct hl_device *hdev,
				struct hl_userptr *userptr)
{
	struct hl_dbg_device_entry *dev_entry = &hdev->hl_debugfs;

	spin_lock(&dev_entry->userptr_spinlock);
	list_del(&userptr->debugfs_list);
	spin_unlock(&dev_entry->userptr_spinlock);
}