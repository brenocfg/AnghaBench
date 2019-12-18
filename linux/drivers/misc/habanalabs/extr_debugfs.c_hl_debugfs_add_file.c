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
struct hl_fpriv {int /*<<< orphan*/  debugfs_list; TYPE_1__* hdev; } ;
struct hl_dbg_device_entry {int /*<<< orphan*/  file_mutex; int /*<<< orphan*/  file_list; } ;
struct TYPE_2__ {struct hl_dbg_device_entry hl_debugfs; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void hl_debugfs_add_file(struct hl_fpriv *hpriv)
{
	struct hl_dbg_device_entry *dev_entry = &hpriv->hdev->hl_debugfs;

	mutex_lock(&dev_entry->file_mutex);
	list_add(&hpriv->debugfs_list, &dev_entry->file_list);
	mutex_unlock(&dev_entry->file_mutex);
}