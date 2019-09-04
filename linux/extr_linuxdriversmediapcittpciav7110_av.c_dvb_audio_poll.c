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
struct file {struct dvb_device* private_data; } ;
struct dvb_device {struct av7110* priv; } ;
struct TYPE_2__ {int /*<<< orphan*/  queue; } ;
struct av7110 {TYPE_1__ aout; scalar_t__ playing; } ;
typedef  int /*<<< orphan*/  poll_table ;
typedef  int __poll_t ;

/* Variables and functions */
 int EPOLLOUT ; 
 int EPOLLWRNORM ; 
 int /*<<< orphan*/  dprintk (int,char*,struct av7110*) ; 
 int dvb_ringbuffer_free (TYPE_1__*) ; 
 int /*<<< orphan*/  poll_wait (struct file*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static __poll_t dvb_audio_poll(struct file *file, poll_table *wait)
{
	struct dvb_device *dvbdev = file->private_data;
	struct av7110 *av7110 = dvbdev->priv;
	__poll_t mask = 0;

	dprintk(2, "av7110:%p, \n", av7110);

	poll_wait(file, &av7110->aout.queue, wait);

	if (av7110->playing) {
		if (dvb_ringbuffer_free(&av7110->aout) >= 20 * 1024)
			mask |= (EPOLLOUT | EPOLLWRNORM);
	} else /* if not playing: may play if asked for */
		mask = (EPOLLOUT | EPOLLWRNORM);

	return mask;
}