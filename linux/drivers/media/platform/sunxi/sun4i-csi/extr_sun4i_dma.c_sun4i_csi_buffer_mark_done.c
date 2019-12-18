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
struct TYPE_4__ {int /*<<< orphan*/  timestamp; } ;
struct vb2_v4l2_buffer {unsigned int sequence; TYPE_2__ vb2_buf; int /*<<< orphan*/  field; } ;
struct TYPE_3__ {int /*<<< orphan*/  field; } ;
struct sun4i_csi {struct vb2_v4l2_buffer** current_buf; TYPE_1__ fmt; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  VB2_BUF_STATE_DONE ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ktime_get_ns () ; 
 int /*<<< orphan*/  vb2_buffer_done (TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sun4i_csi_buffer_mark_done(struct sun4i_csi *csi,
				       unsigned int slot,
				       unsigned int sequence)
{
	struct vb2_v4l2_buffer *v_buf;

	if (!csi->current_buf[slot]) {
		dev_dbg(csi->dev, "Scratch buffer was used, ignoring..\n");
		return;
	}

	v_buf = csi->current_buf[slot];
	v_buf->field = csi->fmt.field;
	v_buf->sequence = sequence;
	v_buf->vb2_buf.timestamp = ktime_get_ns();
	vb2_buffer_done(&v_buf->vb2_buf, VB2_BUF_STATE_DONE);

	csi->current_buf[slot] = NULL;
}