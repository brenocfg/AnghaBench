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
struct smsdvb_debugfs {int /*<<< orphan*/  refcount; int /*<<< orphan*/  stats_queue; } ;
struct file {struct smsdvb_debugfs* private_data; } ;
typedef  int /*<<< orphan*/  poll_table ;
typedef  int __poll_t ;

/* Variables and functions */
 int EPOLLIN ; 
 int EPOLLRDNORM ; 
 int /*<<< orphan*/  kref_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  poll_wait (struct file*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smsdvb_debugfs_data_release ; 
 int smsdvb_stats_wait_read (struct smsdvb_debugfs*) ; 

__attribute__((used)) static __poll_t smsdvb_stats_poll(struct file *file, poll_table *wait)
{
	struct smsdvb_debugfs *debug_data = file->private_data;
	int rc;

	kref_get(&debug_data->refcount);

	poll_wait(file, &debug_data->stats_queue, wait);

	rc = smsdvb_stats_wait_read(debug_data);
	kref_put(&debug_data->refcount, smsdvb_debugfs_data_release);

	return rc > 0 ? EPOLLIN | EPOLLRDNORM : 0;
}