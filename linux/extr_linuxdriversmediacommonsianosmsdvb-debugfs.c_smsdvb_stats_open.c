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
struct smsdvb_debugfs {int stats_was_read; int /*<<< orphan*/  lock; scalar_t__ stats_count; int /*<<< orphan*/  refcount; } ;
struct smsdvb_client_t {struct smsdvb_debugfs* debug_data; } ;
struct inode {struct smsdvb_client_t* i_private; } ;
struct file {struct smsdvb_debugfs* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  kref_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int smsdvb_stats_open(struct inode *inode, struct file *file)
{
	struct smsdvb_client_t *client = inode->i_private;
	struct smsdvb_debugfs *debug_data = client->debug_data;

	kref_get(&debug_data->refcount);

	spin_lock(&debug_data->lock);
	debug_data->stats_count = 0;
	debug_data->stats_was_read = false;
	spin_unlock(&debug_data->lock);

	file->private_data = debug_data;

	return 0;
}