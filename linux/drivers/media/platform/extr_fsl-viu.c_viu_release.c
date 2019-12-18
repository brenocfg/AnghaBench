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
struct viu_fh {int /*<<< orphan*/  fh; int /*<<< orphan*/  vb_vidq; struct viu_dev* dev; } ;
struct viu_dev {int /*<<< orphan*/  users; int /*<<< orphan*/  lock; } ;
struct file {struct viu_fh* private_data; } ;
struct TYPE_2__ {int minor; } ;

/* Variables and functions */
 int /*<<< orphan*/  dprintk (int,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct viu_fh*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_fh_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_fh_exit (int /*<<< orphan*/ *) ; 
 TYPE_1__* video_devdata (struct file*) ; 
 int /*<<< orphan*/  videobuf_mmap_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  videobuf_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  viu_stop_dma (struct viu_dev*) ; 

__attribute__((used)) static int viu_release(struct file *file)
{
	struct viu_fh *fh = file->private_data;
	struct viu_dev *dev = fh->dev;
	int minor = video_devdata(file)->minor;

	mutex_lock(&dev->lock);
	viu_stop_dma(dev);
	videobuf_stop(&fh->vb_vidq);
	videobuf_mmap_free(&fh->vb_vidq);
	v4l2_fh_del(&fh->fh);
	v4l2_fh_exit(&fh->fh);
	mutex_unlock(&dev->lock);

	kfree(fh);

	dev->users--;
	dprintk(1, "close (minor=%d, users=%d)\n",
		minor, dev->users);
	return 0;
}