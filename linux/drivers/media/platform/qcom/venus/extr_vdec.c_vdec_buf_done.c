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
typedef  int u64 ;
typedef  int u32 ;
struct venus_inst {scalar_t__ codec_state; int /*<<< orphan*/  sequence_out; int /*<<< orphan*/  fh; int /*<<< orphan*/  sequence_cap; } ;
struct vb2_buffer {int timestamp; TYPE_1__* planes; } ;
struct vb2_v4l2_buffer {int flags; scalar_t__ sequence; struct vb2_buffer vb2_buf; int /*<<< orphan*/  field; } ;
struct v4l2_event {int /*<<< orphan*/  type; } ;
typedef  enum vb2_buffer_state { ____Placeholder_vb2_buffer_state } vb2_buffer_state ;
struct TYPE_2__ {int data_offset; } ;

/* Variables and functions */
 int HFI_BUFFERFLAG_DATACORRUPT ; 
 int HFI_BUFFERFLAG_DROP_FRAME ; 
 int HFI_BUFFERFLAG_READONLY ; 
 unsigned int HFI_BUFFER_INPUT ; 
 int NSEC_PER_USEC ; 
 int V4L2_BUF_FLAG_LAST ; 
 unsigned int V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE ; 
 unsigned int V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE ; 
 int /*<<< orphan*/  V4L2_EVENT_EOS ; 
 int /*<<< orphan*/  V4L2_FIELD_NONE ; 
 int VB2_BUF_STATE_DONE ; 
 int VB2_BUF_STATE_ERROR ; 
 scalar_t__ VENUS_DEC_STATE_DRAIN ; 
 scalar_t__ VENUS_DEC_STATE_STOPPED ; 
 int /*<<< orphan*/  v4l2_event_queue_fh (int /*<<< orphan*/ *,struct v4l2_event const*) ; 
 int /*<<< orphan*/  v4l2_m2m_buf_done (struct vb2_v4l2_buffer*,int) ; 
 int /*<<< orphan*/  vb2_set_plane_payload (struct vb2_buffer*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  venus_helper_acquire_buf_ref (struct vb2_v4l2_buffer*) ; 
 struct vb2_v4l2_buffer* venus_helper_find_buf (struct venus_inst*,unsigned int,int) ; 
 int /*<<< orphan*/  venus_helper_get_ts_metadata (struct venus_inst*,int,struct vb2_v4l2_buffer*) ; 

__attribute__((used)) static void vdec_buf_done(struct venus_inst *inst, unsigned int buf_type,
			  u32 tag, u32 bytesused, u32 data_offset, u32 flags,
			  u32 hfi_flags, u64 timestamp_us)
{
	enum vb2_buffer_state state = VB2_BUF_STATE_DONE;
	struct vb2_v4l2_buffer *vbuf;
	struct vb2_buffer *vb;
	unsigned int type;

	if (buf_type == HFI_BUFFER_INPUT)
		type = V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE;
	else
		type = V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE;

	vbuf = venus_helper_find_buf(inst, type, tag);
	if (!vbuf)
		return;

	vbuf->flags = flags;
	vbuf->field = V4L2_FIELD_NONE;
	vb = &vbuf->vb2_buf;

	if (type == V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE) {
		vb2_set_plane_payload(vb, 0, bytesused);
		vb->planes[0].data_offset = data_offset;
		vb->timestamp = timestamp_us * NSEC_PER_USEC;
		vbuf->sequence = inst->sequence_cap++;

		if (vbuf->flags & V4L2_BUF_FLAG_LAST) {
			const struct v4l2_event ev = { .type = V4L2_EVENT_EOS };

			v4l2_event_queue_fh(&inst->fh, &ev);

			if (inst->codec_state == VENUS_DEC_STATE_DRAIN)
				inst->codec_state = VENUS_DEC_STATE_STOPPED;
		}
	} else {
		vbuf->sequence = inst->sequence_out++;
	}

	venus_helper_get_ts_metadata(inst, timestamp_us, vbuf);

	if (hfi_flags & HFI_BUFFERFLAG_READONLY)
		venus_helper_acquire_buf_ref(vbuf);

	if (hfi_flags & HFI_BUFFERFLAG_DATACORRUPT)
		state = VB2_BUF_STATE_ERROR;

	if (hfi_flags & HFI_BUFFERFLAG_DROP_FRAME) {
		state = VB2_BUF_STATE_ERROR;
		vb2_set_plane_payload(vb, 0, 0);
		vb->timestamp = 0;
	}

	v4l2_m2m_buf_done(vbuf, state);
}