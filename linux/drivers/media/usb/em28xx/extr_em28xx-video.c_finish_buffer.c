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
struct TYPE_6__ {int /*<<< orphan*/  timestamp; } ;
struct TYPE_4__ {TYPE_3__ vb2_buf; int /*<<< orphan*/  field; scalar_t__ sequence; } ;
struct em28xx_buffer {TYPE_1__ vb; int /*<<< orphan*/  top_field; } ;
struct em28xx {TYPE_2__* v4l2; } ;
struct TYPE_5__ {scalar_t__ progressive; int /*<<< orphan*/  field_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  V4L2_FIELD_INTERLACED ; 
 int /*<<< orphan*/  V4L2_FIELD_NONE ; 
 int /*<<< orphan*/  VB2_BUF_STATE_DONE ; 
 int /*<<< orphan*/  em28xx_isocdbg (char*,struct em28xx_buffer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ktime_get_ns () ; 
 int /*<<< orphan*/  vb2_buffer_done (TYPE_3__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void finish_buffer(struct em28xx *dev,
				 struct em28xx_buffer *buf)
{
	em28xx_isocdbg("[%p/%d] wakeup\n", buf, buf->top_field);

	buf->vb.sequence = dev->v4l2->field_count++;
	if (dev->v4l2->progressive)
		buf->vb.field = V4L2_FIELD_NONE;
	else
		buf->vb.field = V4L2_FIELD_INTERLACED;
	buf->vb.vb2_buf.timestamp = ktime_get_ns();

	vb2_buffer_done(&buf->vb.vb2_buf, VB2_BUF_STATE_DONE);
}