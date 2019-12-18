#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct inode {int dummy; } ;
struct file {int f_flags; struct dvb_device* private_data; } ;
struct dvb_device {struct av7110* priv; } ;
struct TYPE_6__ {scalar_t__ eventw; scalar_t__ eventr; } ;
struct TYPE_5__ {int /*<<< orphan*/  stream_source; } ;
struct TYPE_4__ {int AV_sync_state; } ;
struct av7110 {int video_blank; TYPE_3__ video_events; TYPE_2__ videostate; TYPE_1__ audiostate; int /*<<< orphan*/  avout; int /*<<< orphan*/  aout; } ;

/* Variables and functions */
 int O_ACCMODE ; 
 int O_RDONLY ; 
 int /*<<< orphan*/  VIDEO_SOURCE_DEMUX ; 
 int /*<<< orphan*/  dprintk (int,char*,struct av7110*) ; 
 int dvb_generic_open (struct inode*,struct file*) ; 
 int /*<<< orphan*/  dvb_ringbuffer_flush_spinlock_wakeup (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int dvb_video_open(struct inode *inode, struct file *file)
{
	struct dvb_device *dvbdev = file->private_data;
	struct av7110 *av7110 = dvbdev->priv;
	int err;

	dprintk(2, "av7110:%p, \n", av7110);

	if ((err = dvb_generic_open(inode, file)) < 0)
		return err;

	if ((file->f_flags & O_ACCMODE) != O_RDONLY) {
		dvb_ringbuffer_flush_spinlock_wakeup(&av7110->aout);
		dvb_ringbuffer_flush_spinlock_wakeup(&av7110->avout);
		av7110->video_blank = 1;
		av7110->audiostate.AV_sync_state = 1;
		av7110->videostate.stream_source = VIDEO_SOURCE_DEMUX;

		/*  empty event queue */
		av7110->video_events.eventr = av7110->video_events.eventw = 0;
	}

	return 0;
}