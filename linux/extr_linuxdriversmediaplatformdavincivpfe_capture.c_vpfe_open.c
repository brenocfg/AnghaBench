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
struct vpfe_fh {int /*<<< orphan*/  fh; scalar_t__ io_allowed; struct vpfe_device* vpfe_dev; } ;
struct vpfe_device {int /*<<< orphan*/  lock; int /*<<< orphan*/  usrs; int /*<<< orphan*/  initialized; int /*<<< orphan*/  v4l2_dev; TYPE_1__* cfg; } ;
struct video_device {int dummy; } ;
struct file {struct vpfe_fh* private_data; } ;
struct TYPE_2__ {int /*<<< orphan*/  num_subdevs; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  debug ; 
 int /*<<< orphan*/  kfree (struct vpfe_fh*) ; 
 struct vpfe_fh* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_dbg (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  v4l2_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  v4l2_fh_add (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_fh_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_fh_init (int /*<<< orphan*/ *,struct video_device*) ; 
 struct video_device* video_devdata (struct file*) ; 
 struct vpfe_device* video_drvdata (struct file*) ; 
 scalar_t__ vpfe_initialize_device (struct vpfe_device*) ; 

__attribute__((used)) static int vpfe_open(struct file *file)
{
	struct vpfe_device *vpfe_dev = video_drvdata(file);
	struct video_device *vdev = video_devdata(file);
	struct vpfe_fh *fh;

	v4l2_dbg(1, debug, &vpfe_dev->v4l2_dev, "vpfe_open\n");

	if (!vpfe_dev->cfg->num_subdevs) {
		v4l2_err(&vpfe_dev->v4l2_dev, "No decoder registered\n");
		return -ENODEV;
	}

	/* Allocate memory for the file handle object */
	fh = kmalloc(sizeof(*fh), GFP_KERNEL);
	if (!fh)
		return -ENOMEM;

	/* store pointer to fh in private_data member of file */
	file->private_data = fh;
	fh->vpfe_dev = vpfe_dev;
	v4l2_fh_init(&fh->fh, vdev);
	mutex_lock(&vpfe_dev->lock);
	/* If decoder is not initialized. initialize it */
	if (!vpfe_dev->initialized) {
		if (vpfe_initialize_device(vpfe_dev)) {
			mutex_unlock(&vpfe_dev->lock);
			v4l2_fh_exit(&fh->fh);
			kfree(fh);
			return -ENODEV;
		}
	}
	/* Increment device usrs counter */
	vpfe_dev->usrs++;
	/* Set io_allowed member to false */
	fh->io_allowed = 0;
	v4l2_fh_add(&fh->fh);
	mutex_unlock(&vpfe_dev->lock);
	return 0;
}