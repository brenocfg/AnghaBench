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
struct inode {struct bnad* i_private; } ;
struct file {struct bnad_debug_info* private_data; } ;
struct bnad_drvinfo {int dummy; } ;
struct bnad_debug_info {int buffer_len; struct bnad_debug_info* debug_buffer; } ;
struct bnad {int /*<<< orphan*/  netdev; int /*<<< orphan*/  conf_mutex; } ;

/* Variables and functions */
 int BFA_STATUS_OK ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int bnad_get_debug_drvinfo (struct bnad*,struct bnad_debug_info*,int) ; 
 int /*<<< orphan*/  kfree (struct bnad_debug_info*) ; 
 void* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netdev_warn (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
bnad_debugfs_open_drvinfo(struct inode *inode, struct file *file)
{
	struct bnad *bnad = inode->i_private;
	struct bnad_debug_info *drv_info;
	int rc;

	drv_info = kzalloc(sizeof(struct bnad_debug_info), GFP_KERNEL);
	if (!drv_info)
		return -ENOMEM;

	drv_info->buffer_len = sizeof(struct bnad_drvinfo);

	drv_info->debug_buffer = kzalloc(drv_info->buffer_len, GFP_KERNEL);
	if (!drv_info->debug_buffer) {
		kfree(drv_info);
		drv_info = NULL;
		return -ENOMEM;
	}

	mutex_lock(&bnad->conf_mutex);
	rc = bnad_get_debug_drvinfo(bnad, drv_info->debug_buffer,
				drv_info->buffer_len);
	mutex_unlock(&bnad->conf_mutex);
	if (rc != BFA_STATUS_OK) {
		kfree(drv_info->debug_buffer);
		drv_info->debug_buffer = NULL;
		kfree(drv_info);
		drv_info = NULL;
		netdev_warn(bnad->netdev, "failed to collect drvinfo\n");
		return -ENOMEM;
	}

	file->private_data = drv_info;

	return 0;
}