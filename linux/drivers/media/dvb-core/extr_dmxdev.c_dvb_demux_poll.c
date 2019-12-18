#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct file {struct dmxdev_filter* private_data; } ;
struct TYPE_4__ {scalar_t__ error; int /*<<< orphan*/  queue; } ;
struct dmxdev_filter {scalar_t__ state; TYPE_2__ buffer; int /*<<< orphan*/  vb2_ctx; TYPE_1__* dev; } ;
typedef  int /*<<< orphan*/  poll_table ;
typedef  int __poll_t ;
struct TYPE_3__ {scalar_t__ exit; } ;

/* Variables and functions */
 scalar_t__ DMXDEV_STATE_DONE ; 
 scalar_t__ DMXDEV_STATE_GO ; 
 scalar_t__ DMXDEV_STATE_TIMEDOUT ; 
 int EPOLLERR ; 
 int EPOLLIN ; 
 int EPOLLPRI ; 
 int EPOLLRDNORM ; 
 int /*<<< orphan*/  dvb_ringbuffer_empty (TYPE_2__*) ; 
 scalar_t__ dvb_vb2_is_streaming (int /*<<< orphan*/ *) ; 
 int dvb_vb2_poll (int /*<<< orphan*/ *,struct file*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  poll_wait (struct file*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static __poll_t dvb_demux_poll(struct file *file, poll_table *wait)
{
	struct dmxdev_filter *dmxdevfilter = file->private_data;
	__poll_t mask = 0;

	poll_wait(file, &dmxdevfilter->buffer.queue, wait);

	if ((!dmxdevfilter) || dmxdevfilter->dev->exit)
		return EPOLLERR;
	if (dvb_vb2_is_streaming(&dmxdevfilter->vb2_ctx))
		return dvb_vb2_poll(&dmxdevfilter->vb2_ctx, file, wait);

	if (dmxdevfilter->state != DMXDEV_STATE_GO &&
	    dmxdevfilter->state != DMXDEV_STATE_DONE &&
	    dmxdevfilter->state != DMXDEV_STATE_TIMEDOUT)
		return 0;

	if (dmxdevfilter->buffer.error)
		mask |= (EPOLLIN | EPOLLRDNORM | EPOLLPRI | EPOLLERR);

	if (!dvb_ringbuffer_empty(&dmxdevfilter->buffer))
		mask |= (EPOLLIN | EPOLLRDNORM | EPOLLPRI);

	return mask;
}