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
struct tm6000_dmaqueue {int dummy; } ;
struct tm6000_core {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  done; int /*<<< orphan*/  queue; int /*<<< orphan*/  ts; int /*<<< orphan*/  field_count; int /*<<< orphan*/  state; int /*<<< orphan*/  i; } ;
struct tm6000_buffer {TYPE_1__ vb; } ;

/* Variables and functions */
 int /*<<< orphan*/  V4L2_DEBUG_ISOC ; 
 int /*<<< orphan*/  VIDEOBUF_DONE ; 
 int /*<<< orphan*/  dprintk (struct tm6000_core*,int /*<<< orphan*/ ,char*,struct tm6000_buffer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ktime_get_ns () ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void buffer_filled(struct tm6000_core *dev,
				 struct tm6000_dmaqueue *dma_q,
				 struct tm6000_buffer *buf)
{
	/* Advice that buffer was filled */
	dprintk(dev, V4L2_DEBUG_ISOC, "[%p/%d] wakeup\n", buf, buf->vb.i);
	buf->vb.state = VIDEOBUF_DONE;
	buf->vb.field_count++;
	buf->vb.ts = ktime_get_ns();

	list_del(&buf->vb.queue);
	wake_up(&buf->vb.done);
}