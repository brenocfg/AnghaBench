#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct cx18_stream {scalar_t__ type; int /*<<< orphan*/  waitq; int /*<<< orphan*/  s_flags; int /*<<< orphan*/  handle; struct cx18* cx; } ;
struct cx18 {int /*<<< orphan*/  cxhdl; int /*<<< orphan*/  tot_capturing; int /*<<< orphan*/  ana_capturing; } ;

/* Variables and functions */
 int /*<<< orphan*/  CX18_CPU_CAPTURE_STOP ; 
 int /*<<< orphan*/  CX18_CPU_DE_RELEASE_MDL ; 
 int /*<<< orphan*/  CX18_DEBUG_INFO (char*) ; 
 int /*<<< orphan*/  CX18_DESTROY_TASK ; 
 int /*<<< orphan*/  CX18_DSP0_INTERRUPT_MASK ; 
 scalar_t__ CX18_ENC_STREAM_TYPE_MPG ; 
 scalar_t__ CX18_ENC_STREAM_TYPE_TS ; 
 int /*<<< orphan*/  CX18_F_S_STOPPING ; 
 int /*<<< orphan*/  CX18_F_S_STREAMING ; 
 int /*<<< orphan*/  CX18_INFO (char*) ; 
 int /*<<< orphan*/  CX18_INVALID_TASK_HANDLE ; 
 int EINVAL ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cx18_stream_enabled (struct cx18_stream*) ; 
 int /*<<< orphan*/  cx18_vapi (struct cx18*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  cx18_write_reg (struct cx18*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cx2341x_handler_set_busy (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

int cx18_stop_v4l2_encode_stream(struct cx18_stream *s, int gop_end)
{
	struct cx18 *cx = s->cx;

	if (!cx18_stream_enabled(s))
		return -EINVAL;

	/* This function assumes that you are allowed to stop the capture
	   and that we are actually capturing */

	CX18_DEBUG_INFO("Stop Capture\n");

	if (atomic_read(&cx->tot_capturing) == 0)
		return 0;

	set_bit(CX18_F_S_STOPPING, &s->s_flags);
	if (s->type == CX18_ENC_STREAM_TYPE_MPG)
		cx18_vapi(cx, CX18_CPU_CAPTURE_STOP, 2, s->handle, !gop_end);
	else
		cx18_vapi(cx, CX18_CPU_CAPTURE_STOP, 1, s->handle);

	if (s->type == CX18_ENC_STREAM_TYPE_MPG && gop_end) {
		CX18_INFO("ignoring gop_end: not (yet?) supported by the firmware\n");
	}

	if (s->type != CX18_ENC_STREAM_TYPE_TS)
		atomic_dec(&cx->ana_capturing);
	atomic_dec(&cx->tot_capturing);

	/* Clear capture and no-read bits */
	clear_bit(CX18_F_S_STREAMING, &s->s_flags);

	/* Tell the CX23418 it can't use our buffers anymore */
	cx18_vapi(cx, CX18_CPU_DE_RELEASE_MDL, 1, s->handle);

	cx18_vapi(cx, CX18_DESTROY_TASK, 1, s->handle);
	s->handle = CX18_INVALID_TASK_HANDLE;
	clear_bit(CX18_F_S_STOPPING, &s->s_flags);

	if (atomic_read(&cx->tot_capturing) > 0)
		return 0;

	cx2341x_handler_set_busy(&cx->cxhdl, 0);
	cx18_write_reg(cx, 5, CX18_DSP0_INTERRUPT_MASK);
	wake_up(&s->waitq);

	return 0;
}