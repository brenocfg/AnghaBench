#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct file {struct cx231xx_fh* private_data; } ;
struct TYPE_4__ {scalar_t__ reading; scalar_t__ streaming; } ;
struct cx231xx_fh {int /*<<< orphan*/  fh; TYPE_1__ vidq; int /*<<< orphan*/  v4l_reading; struct cx231xx* dev; } ;
struct cx231xx {int /*<<< orphan*/  lock; int /*<<< orphan*/  v4l_reader_count; scalar_t__ USE_ISO; } ;

/* Variables and functions */
 int /*<<< orphan*/  CX231XX_SUSPEND ; 
 int /*<<< orphan*/  CX231xx_END_NOW ; 
 int /*<<< orphan*/  CX231xx_MPEG_CAPTURE ; 
 int /*<<< orphan*/  CX231xx_RAW_BITS_NONE ; 
 int /*<<< orphan*/  CX2341X_ENC_STOP_CAPTURE ; 
 int atomic_cmpxchg (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 scalar_t__ atomic_dec_return (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cx231xx_417_check_encoder (struct cx231xx*) ; 
 int /*<<< orphan*/  cx231xx_api_cmd (struct cx231xx*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cx231xx_set_mode (struct cx231xx*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cx231xx_stop_TS1 (struct cx231xx*) ; 
 int /*<<< orphan*/  cx231xx_uninit_bulk (struct cx231xx*) ; 
 int /*<<< orphan*/  cx231xx_uninit_isoc (struct cx231xx*) ; 
 int /*<<< orphan*/  dprintk (int,char*,struct cx231xx*) ; 
 int /*<<< orphan*/  kfree (struct cx231xx_fh*) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_fh_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_fh_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  videobuf_mmap_free (TYPE_1__*) ; 
 int /*<<< orphan*/  videobuf_read_stop (TYPE_1__*) ; 
 int /*<<< orphan*/  videobuf_streamoff (TYPE_1__*) ; 

__attribute__((used)) static int mpeg_release(struct file *file)
{
	struct cx231xx_fh  *fh  = file->private_data;
	struct cx231xx *dev = fh->dev;

	dprintk(3, "mpeg_release()! dev=0x%p\n", dev);

	mutex_lock(&dev->lock);

	cx231xx_stop_TS1(dev);

	/* do this before setting alternate! */
	if (dev->USE_ISO)
		cx231xx_uninit_isoc(dev);
	else
		cx231xx_uninit_bulk(dev);
	cx231xx_set_mode(dev, CX231XX_SUSPEND);

	cx231xx_api_cmd(fh->dev, CX2341X_ENC_STOP_CAPTURE, 3, 0,
			CX231xx_END_NOW, CX231xx_MPEG_CAPTURE,
			CX231xx_RAW_BITS_NONE);

	/* FIXME: Review this crap */
	/* Shut device down on last close */
	if (atomic_cmpxchg(&fh->v4l_reading, 1, 0) == 1) {
		if (atomic_dec_return(&dev->v4l_reader_count) == 0) {
			/* stop mpeg capture */

			msleep(500);
			cx231xx_417_check_encoder(dev);

		}
	}

	if (fh->vidq.streaming)
		videobuf_streamoff(&fh->vidq);
	if (fh->vidq.reading)
		videobuf_read_stop(&fh->vidq);

	videobuf_mmap_free(&fh->vidq);
	v4l2_fh_del(&fh->fh);
	v4l2_fh_exit(&fh->fh);
	kfree(fh);
	mutex_unlock(&dev->lock);
	return 0;
}