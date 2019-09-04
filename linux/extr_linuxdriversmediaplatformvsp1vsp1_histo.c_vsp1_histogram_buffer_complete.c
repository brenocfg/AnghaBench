#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct vsp1_pipeline {int /*<<< orphan*/  sequence; } ;
struct TYPE_7__ {int /*<<< orphan*/  timestamp; } ;
struct TYPE_5__ {TYPE_3__ vb2_buf; int /*<<< orphan*/  sequence; } ;
struct vsp1_histogram_buffer {TYPE_1__ buf; } ;
struct TYPE_6__ {struct vsp1_pipeline* pipe; } ;
struct vsp1_histogram {int readout; int /*<<< orphan*/  irqlock; int /*<<< orphan*/  wait_queue; TYPE_2__ entity; } ;

/* Variables and functions */
 int /*<<< orphan*/  VB2_BUF_STATE_DONE ; 
 int /*<<< orphan*/  ktime_get_ns () ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  vb2_buffer_done (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vb2_set_plane_payload (TYPE_3__*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

void vsp1_histogram_buffer_complete(struct vsp1_histogram *histo,
				    struct vsp1_histogram_buffer *buf,
				    size_t size)
{
	struct vsp1_pipeline *pipe = histo->entity.pipe;
	unsigned long flags;

	/*
	 * The pipeline pointer is guaranteed to be valid as this function is
	 * called from the frame completion interrupt handler, which can only
	 * occur when video streaming is active.
	 */
	buf->buf.sequence = pipe->sequence;
	buf->buf.vb2_buf.timestamp = ktime_get_ns();
	vb2_set_plane_payload(&buf->buf.vb2_buf, 0, size);
	vb2_buffer_done(&buf->buf.vb2_buf, VB2_BUF_STATE_DONE);

	spin_lock_irqsave(&histo->irqlock, flags);
	histo->readout = false;
	wake_up(&histo->wait_queue);
	spin_unlock_irqrestore(&histo->irqlock, flags);
}