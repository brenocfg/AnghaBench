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
struct inode {int dummy; } ;
struct imon_context {int display_isopen; int /*<<< orphan*/  lock; int /*<<< orphan*/  dev; int /*<<< orphan*/  display_supported; } ;
struct file {struct imon_context* private_data; } ;

/* Variables and functions */
 int EIO ; 
 int ENODEV ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*) ; 

__attribute__((used)) static int display_close(struct inode *inode, struct file *file)
{
	struct imon_context *ictx = NULL;
	int retval = 0;

	ictx = file->private_data;

	if (!ictx) {
		pr_err("no context for device\n");
		return -ENODEV;
	}

	mutex_lock(&ictx->lock);

	if (!ictx->display_supported) {
		pr_err("display not supported by device\n");
		retval = -ENODEV;
	} else if (!ictx->display_isopen) {
		pr_err("display is not open\n");
		retval = -EIO;
	} else {
		ictx->display_isopen = false;
		dev_dbg(ictx->dev, "display port closed\n");
	}

	mutex_unlock(&ictx->lock);
	return retval;
}