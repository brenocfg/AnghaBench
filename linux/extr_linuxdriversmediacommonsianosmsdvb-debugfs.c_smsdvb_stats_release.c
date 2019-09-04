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
struct smsdvb_debugfs {int stats_was_read; int /*<<< orphan*/  refcount; int /*<<< orphan*/  stats_queue; int /*<<< orphan*/  lock; } ;
struct inode {int dummy; } ;
struct file {struct smsdvb_debugfs* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smsdvb_debugfs_data_release ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up_interruptible_sync (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int smsdvb_stats_release(struct inode *inode, struct file *file)
{
	struct smsdvb_debugfs *debug_data = file->private_data;

	spin_lock(&debug_data->lock);
	debug_data->stats_was_read = true;	/* return EOF to read() */
	spin_unlock(&debug_data->lock);
	wake_up_interruptible_sync(&debug_data->stats_queue);

	kref_put(&debug_data->refcount, smsdvb_debugfs_data_release);
	file->private_data = NULL;

	return 0;
}