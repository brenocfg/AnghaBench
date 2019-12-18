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
struct hl_dbg_device_entry {int /*<<< orphan*/  cs_job_spinlock; int /*<<< orphan*/  cs_job_list; } ;
struct hl_device {struct hl_dbg_device_entry hl_debugfs; } ;
struct hl_cs_job {int /*<<< orphan*/  debugfs_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void hl_debugfs_add_job(struct hl_device *hdev, struct hl_cs_job *job)
{
	struct hl_dbg_device_entry *dev_entry = &hdev->hl_debugfs;

	spin_lock(&dev_entry->cs_job_spinlock);
	list_add(&job->debugfs_list, &dev_entry->cs_job_list);
	spin_unlock(&dev_entry->cs_job_spinlock);
}