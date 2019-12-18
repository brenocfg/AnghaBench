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
struct hl_dbg_device_entry {int /*<<< orphan*/  cb_spinlock; } ;
struct hl_cb {int /*<<< orphan*/  debugfs_list; TYPE_1__* hdev; } ;
struct TYPE_2__ {struct hl_dbg_device_entry hl_debugfs; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void hl_debugfs_remove_cb(struct hl_cb *cb)
{
	struct hl_dbg_device_entry *dev_entry = &cb->hdev->hl_debugfs;

	spin_lock(&dev_entry->cb_spinlock);
	list_del(&cb->debugfs_list);
	spin_unlock(&dev_entry->cb_spinlock);
}