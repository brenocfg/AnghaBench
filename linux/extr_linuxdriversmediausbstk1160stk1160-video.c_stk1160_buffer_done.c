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
struct TYPE_6__ {TYPE_3__ vb2_buf; int /*<<< orphan*/  field; scalar_t__ sequence; } ;
struct stk1160_buffer {TYPE_2__ vb; int /*<<< orphan*/  bytesused; } ;
struct TYPE_5__ {struct stk1160_buffer* buf; } ;
struct stk1160 {TYPE_1__ isoc_ctl; int /*<<< orphan*/  sequence; } ;

/* Variables and functions */
 int /*<<< orphan*/  V4L2_FIELD_INTERLACED ; 
 int /*<<< orphan*/  VB2_BUF_STATE_DONE ; 
 int /*<<< orphan*/  ktime_get_ns () ; 
 int /*<<< orphan*/  vb2_buffer_done (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vb2_set_plane_payload (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline
void stk1160_buffer_done(struct stk1160 *dev)
{
	struct stk1160_buffer *buf = dev->isoc_ctl.buf;

	buf->vb.sequence = dev->sequence++;
	buf->vb.field = V4L2_FIELD_INTERLACED;
	buf->vb.vb2_buf.timestamp = ktime_get_ns();

	vb2_set_plane_payload(&buf->vb.vb2_buf, 0, buf->bytesused);
	vb2_buffer_done(&buf->vb.vb2_buf, VB2_BUF_STATE_DONE);

	dev->isoc_ctl.buf = NULL;
}