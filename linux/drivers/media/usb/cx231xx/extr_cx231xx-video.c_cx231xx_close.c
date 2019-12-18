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
struct file {struct cx231xx_fh* private_data; } ;
struct cx231xx_fh {scalar_t__ type; int /*<<< orphan*/  fh; struct cx231xx* dev; int /*<<< orphan*/  vb_vidq; } ;
struct TYPE_2__ {int /*<<< orphan*/  no_alt_vanc; } ;
struct cx231xx {int state; int /*<<< orphan*/  open; scalar_t__ USE_ISO; int /*<<< orphan*/  users; int /*<<< orphan*/  vbi_or_sliced_cc_mode; int /*<<< orphan*/  devlist_count; TYPE_1__ board; } ;

/* Variables and functions */
 int /*<<< orphan*/  CX231XX_SUSPEND ; 
 int DEV_DISCONNECTED ; 
 int /*<<< orphan*/  INDEX_HANC ; 
 int /*<<< orphan*/  INDEX_VANC ; 
 int /*<<< orphan*/  INDEX_VIDEO ; 
 scalar_t__ V4L2_BUF_TYPE_VBI_CAPTURE ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  call_all (struct cx231xx*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cx231xx_release_resources (struct cx231xx*) ; 
 int /*<<< orphan*/  cx231xx_set_alt_setting (struct cx231xx*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cx231xx_set_mode (struct cx231xx*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cx231xx_uninit_bulk (struct cx231xx*) ; 
 int /*<<< orphan*/  cx231xx_uninit_isoc (struct cx231xx*) ; 
 int /*<<< orphan*/  cx231xx_uninit_vbi_isoc (struct cx231xx*) ; 
 int /*<<< orphan*/  cx231xx_videodbg (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct cx231xx_fh*) ; 
 scalar_t__ res_check (struct cx231xx_fh*) ; 
 int /*<<< orphan*/  res_free (struct cx231xx_fh*) ; 
 int /*<<< orphan*/  standby ; 
 int /*<<< orphan*/  tuner ; 
 int /*<<< orphan*/  v4l2_fh_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_fh_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  videobuf_mmap_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  videobuf_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int cx231xx_close(struct file *filp)
{
	struct cx231xx_fh *fh = filp->private_data;
	struct cx231xx *dev = fh->dev;

	cx231xx_videodbg("users=%d\n", dev->users);

	cx231xx_videodbg("users=%d\n", dev->users);
	if (res_check(fh))
		res_free(fh);

	/*
	 * To workaround error number=-71 on EP0 for VideoGrabber,
	 *	 need exclude following.
	 * FIXME: It is probably safe to remove most of these, as we're
	 * now avoiding the alternate setting for INDEX_VANC
	 */
	if (!dev->board.no_alt_vanc)
		if (fh->type == V4L2_BUF_TYPE_VBI_CAPTURE) {
			videobuf_stop(&fh->vb_vidq);
			videobuf_mmap_free(&fh->vb_vidq);

			/* the device is already disconnect,
			   free the remaining resources */
			if (dev->state & DEV_DISCONNECTED) {
				if (atomic_read(&dev->devlist_count) > 0) {
					cx231xx_release_resources(dev);
					fh->dev = NULL;
					return 0;
				}
				return 0;
			}

			/* do this before setting alternate! */
			cx231xx_uninit_vbi_isoc(dev);

			/* set alternate 0 */
			if (!dev->vbi_or_sliced_cc_mode)
				cx231xx_set_alt_setting(dev, INDEX_VANC, 0);
			else
				cx231xx_set_alt_setting(dev, INDEX_HANC, 0);

			v4l2_fh_del(&fh->fh);
			v4l2_fh_exit(&fh->fh);
			kfree(fh);
			dev->users--;
			wake_up_interruptible(&dev->open);
			return 0;
		}

	v4l2_fh_del(&fh->fh);
	dev->users--;
	if (!dev->users) {
		videobuf_stop(&fh->vb_vidq);
		videobuf_mmap_free(&fh->vb_vidq);

		/* the device is already disconnect,
		   free the remaining resources */
		if (dev->state & DEV_DISCONNECTED) {
			cx231xx_release_resources(dev);
			fh->dev = NULL;
			return 0;
		}

		/* Save some power by putting tuner to sleep */
		call_all(dev, tuner, standby);

		/* do this before setting alternate! */
		if (dev->USE_ISO)
			cx231xx_uninit_isoc(dev);
		else
			cx231xx_uninit_bulk(dev);
		cx231xx_set_mode(dev, CX231XX_SUSPEND);

		/* set alternate 0 */
		cx231xx_set_alt_setting(dev, INDEX_VIDEO, 0);
	}
	v4l2_fh_exit(&fh->fh);
	kfree(fh);
	wake_up_interruptible(&dev->open);
	return 0;
}