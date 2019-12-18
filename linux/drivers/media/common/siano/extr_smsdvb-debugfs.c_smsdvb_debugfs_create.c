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
struct smsdvb_debugfs {int /*<<< orphan*/  refcount; int /*<<< orphan*/  lock; int /*<<< orphan*/  stats_queue; } ;
struct smsdvb_client_t {int /*<<< orphan*/  prt_isdb_stats_ex; int /*<<< orphan*/  prt_isdb_stats; int /*<<< orphan*/  prt_dvb_stats; struct smsdvb_debugfs* debug_data; int /*<<< orphan*/  debugfs; struct smscore_device_t* coredev; } ;
struct smscore_device_t {int /*<<< orphan*/  devpath; int /*<<< orphan*/  is_usb_device; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR_OR_NULL (int /*<<< orphan*/ ) ; 
 int S_IRUGO ; 
 int S_IWUSR ; 
 int /*<<< orphan*/  debugfs_create_dir (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct dentry* debugfs_create_file (char*,int,int /*<<< orphan*/ ,struct smsdvb_client_t*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debugfs_remove (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugfs_stats_ops ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 
 struct smsdvb_debugfs* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smsdvb_debugfs_usb_root ; 
 int /*<<< orphan*/  smsdvb_print_dvb_stats ; 
 int /*<<< orphan*/  smsdvb_print_isdb_stats ; 
 int /*<<< orphan*/  smsdvb_print_isdb_stats_ex ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

int smsdvb_debugfs_create(struct smsdvb_client_t *client)
{
	struct smscore_device_t *coredev = client->coredev;
	struct dentry *d;
	struct smsdvb_debugfs *debug_data;

	if (!smsdvb_debugfs_usb_root || !coredev->is_usb_device)
		return -ENODEV;

	client->debugfs = debugfs_create_dir(coredev->devpath,
					     smsdvb_debugfs_usb_root);
	if (IS_ERR_OR_NULL(client->debugfs)) {
		pr_info("Unable to create debugfs %s directory.\n",
			coredev->devpath);
		return -ENODEV;
	}

	d = debugfs_create_file("stats", S_IRUGO | S_IWUSR, client->debugfs,
				client, &debugfs_stats_ops);
	if (!d) {
		debugfs_remove(client->debugfs);
		return -ENOMEM;
	}

	debug_data = kzalloc(sizeof(*client->debug_data), GFP_KERNEL);
	if (!debug_data)
		return -ENOMEM;

	client->debug_data        = debug_data;
	client->prt_dvb_stats     = smsdvb_print_dvb_stats;
	client->prt_isdb_stats    = smsdvb_print_isdb_stats;
	client->prt_isdb_stats_ex = smsdvb_print_isdb_stats_ex;

	init_waitqueue_head(&debug_data->stats_queue);
	spin_lock_init(&debug_data->lock);
	kref_init(&debug_data->refcount);

	return 0;
}