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
struct venus_inst {scalar_t__ session_type; int /*<<< orphan*/  opb_buftype; } ;
struct venus_buffer {int /*<<< orphan*/  dma_addr; int /*<<< orphan*/  size; } ;
struct vb2_buffer {unsigned int type; TYPE_1__* planes; int /*<<< orphan*/  index; int /*<<< orphan*/  timestamp; } ;
struct vb2_v4l2_buffer {int flags; struct vb2_buffer vb2_buf; } ;
struct hfi_frame_data {scalar_t__ offset; scalar_t__ filled_len; int /*<<< orphan*/  buffer_type; int /*<<< orphan*/  flags; int /*<<< orphan*/  clnt_data; int /*<<< orphan*/  timestamp; int /*<<< orphan*/  device_addr; int /*<<< orphan*/  alloc_len; } ;
typedef  int /*<<< orphan*/  fdata ;
struct TYPE_2__ {scalar_t__ data_offset; } ;

/* Variables and functions */
 int /*<<< orphan*/  HFI_BUFFERFLAG_EOS ; 
 int /*<<< orphan*/  HFI_BUFFER_INPUT ; 
 int /*<<< orphan*/  HFI_BUFFER_OUTPUT ; 
 int /*<<< orphan*/  NSEC_PER_USEC ; 
 int V4L2_BUF_FLAG_LAST ; 
 unsigned int V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE ; 
 unsigned int V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE ; 
 scalar_t__ VIDC_SESSION_TYPE_DEC ; 
 scalar_t__ VIDC_SESSION_TYPE_ENC ; 
 int /*<<< orphan*/  do_div (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int hfi_session_process_buf (struct venus_inst*,struct hfi_frame_data*) ; 
 int /*<<< orphan*/  memset (struct hfi_frame_data*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  put_ts_metadata (struct venus_inst*,struct vb2_v4l2_buffer*) ; 
 struct venus_buffer* to_venus_buffer (struct vb2_v4l2_buffer*) ; 
 scalar_t__ vb2_get_plane_payload (struct vb2_buffer*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
session_process_buf(struct venus_inst *inst, struct vb2_v4l2_buffer *vbuf)
{
	struct venus_buffer *buf = to_venus_buffer(vbuf);
	struct vb2_buffer *vb = &vbuf->vb2_buf;
	unsigned int type = vb->type;
	struct hfi_frame_data fdata;
	int ret;

	memset(&fdata, 0, sizeof(fdata));
	fdata.alloc_len = buf->size;
	fdata.device_addr = buf->dma_addr;
	fdata.timestamp = vb->timestamp;
	do_div(fdata.timestamp, NSEC_PER_USEC);
	fdata.flags = 0;
	fdata.clnt_data = vbuf->vb2_buf.index;

	if (type == V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE) {
		fdata.buffer_type = HFI_BUFFER_INPUT;
		fdata.filled_len = vb2_get_plane_payload(vb, 0);
		fdata.offset = vb->planes[0].data_offset;

		if (vbuf->flags & V4L2_BUF_FLAG_LAST || !fdata.filled_len)
			fdata.flags |= HFI_BUFFERFLAG_EOS;

		if (inst->session_type == VIDC_SESSION_TYPE_DEC)
			put_ts_metadata(inst, vbuf);
	} else if (type == V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE) {
		if (inst->session_type == VIDC_SESSION_TYPE_ENC)
			fdata.buffer_type = HFI_BUFFER_OUTPUT;
		else
			fdata.buffer_type = inst->opb_buftype;
		fdata.filled_len = 0;
		fdata.offset = 0;
	}

	ret = hfi_session_process_buf(inst, &fdata);
	if (ret)
		return ret;

	return 0;
}