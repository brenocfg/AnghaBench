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
struct hl_dbg_device_entry {int /*<<< orphan*/  entry_arr; int /*<<< orphan*/  file_mutex; int /*<<< orphan*/  root; } ;
struct hl_device {struct hl_dbg_device_entry hl_debugfs; } ;

/* Variables and functions */
 int /*<<< orphan*/  debugfs_remove_recursive (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 

void hl_debugfs_remove_device(struct hl_device *hdev)
{
	struct hl_dbg_device_entry *entry = &hdev->hl_debugfs;

	debugfs_remove_recursive(entry->root);

	mutex_destroy(&entry->file_mutex);
	kfree(entry->entry_arr);
}