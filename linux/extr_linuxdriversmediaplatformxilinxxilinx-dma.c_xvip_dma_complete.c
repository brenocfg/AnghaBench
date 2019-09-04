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
struct TYPE_7__ {int /*<<< orphan*/  timestamp; } ;
struct TYPE_6__ {TYPE_3__ vb2_buf; scalar_t__ sequence; int /*<<< orphan*/  field; } ;
struct xvip_dma_buffer {TYPE_2__ buf; int /*<<< orphan*/  queue; struct xvip_dma* dma; } ;
struct TYPE_5__ {int /*<<< orphan*/  sizeimage; } ;
struct xvip_dma {TYPE_1__ format; int /*<<< orphan*/  sequence; int /*<<< orphan*/  queued_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  V4L2_FIELD_NONE ; 
 int /*<<< orphan*/  VB2_BUF_STATE_DONE ; 
 int /*<<< orphan*/  ktime_get_ns () ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vb2_buffer_done (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vb2_set_plane_payload (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void xvip_dma_complete(void *param)
{
	struct xvip_dma_buffer *buf = param;
	struct xvip_dma *dma = buf->dma;

	spin_lock(&dma->queued_lock);
	list_del(&buf->queue);
	spin_unlock(&dma->queued_lock);

	buf->buf.field = V4L2_FIELD_NONE;
	buf->buf.sequence = dma->sequence++;
	buf->buf.vb2_buf.timestamp = ktime_get_ns();
	vb2_set_plane_payload(&buf->buf.vb2_buf, 0, dma->format.sizeimage);
	vb2_buffer_done(&buf->buf.vb2_buf, VB2_BUF_STATE_DONE);
}