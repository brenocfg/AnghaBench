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
typedef  scalar_t__ u32 ;
struct vb2_buffer {int /*<<< orphan*/  timestamp; } ;
struct vb2_v4l2_buffer {int /*<<< orphan*/  field; scalar_t__ flags; struct vb2_buffer vb2_buf; } ;
struct amvdec_session {int /*<<< orphan*/  esparser_queued_bufs; scalar_t__ keyframe_found; int /*<<< orphan*/  m2m_ctx; TYPE_1__* fmt_out; struct amvdec_core* core; } ;
struct amvdec_core {int /*<<< orphan*/  dev; } ;
struct amvdec_codec_ops {scalar_t__ (* num_pending_bufs ) (struct amvdec_session*) ;} ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_2__ {struct amvdec_codec_ops* codec_ops; } ;

/* Variables and functions */
 int EAGAIN ; 
 int /*<<< orphan*/  PARSER_FETCH_CMD ; 
 int /*<<< orphan*/  V4L2_FIELD_NONE ; 
 int /*<<< orphan*/  VB2_BUF_STATE_DONE ; 
 int /*<<< orphan*/  VB2_BUF_STATE_ERROR ; 
 int /*<<< orphan*/  amvdec_add_ts_reorder (struct amvdec_session*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  amvdec_remove_ts (struct amvdec_session*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  amvdec_write_parser (struct amvdec_core*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ esparser_get_offset (struct amvdec_session*) ; 
 scalar_t__ esparser_pad_start_code (struct vb2_buffer*) ; 
 scalar_t__ esparser_vififo_get_free_space (struct amvdec_session*) ; 
 int esparser_write_data (struct amvdec_core*,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ stub1 (struct amvdec_session*) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 
 int /*<<< orphan*/  v4l2_m2m_buf_done (struct vb2_v4l2_buffer*,int /*<<< orphan*/ ) ; 
 scalar_t__ v4l2_m2m_num_dst_bufs_ready (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_m2m_src_buf_remove_by_buf (int /*<<< orphan*/ ,struct vb2_v4l2_buffer*) ; 
 int /*<<< orphan*/  vb2_dma_contig_plane_dma_addr (struct vb2_buffer*,int /*<<< orphan*/ ) ; 
 scalar_t__ vb2_get_plane_payload (struct vb2_buffer*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
esparser_queue(struct amvdec_session *sess, struct vb2_v4l2_buffer *vbuf)
{
	int ret;
	struct vb2_buffer *vb = &vbuf->vb2_buf;
	struct amvdec_core *core = sess->core;
	struct amvdec_codec_ops *codec_ops = sess->fmt_out->codec_ops;
	u32 num_dst_bufs = 0;
	u32 payload_size = vb2_get_plane_payload(vb, 0);
	dma_addr_t phy = vb2_dma_contig_plane_dma_addr(vb, 0);
	u32 offset;
	u32 pad_size;

	if (codec_ops->num_pending_bufs)
		num_dst_bufs = codec_ops->num_pending_bufs(sess);

	num_dst_bufs += v4l2_m2m_num_dst_bufs_ready(sess->m2m_ctx);

	if (esparser_vififo_get_free_space(sess) < payload_size ||
	    atomic_read(&sess->esparser_queued_bufs) >= num_dst_bufs)
		return -EAGAIN;

	v4l2_m2m_src_buf_remove_by_buf(sess->m2m_ctx, vbuf);

	offset = esparser_get_offset(sess);

	amvdec_add_ts_reorder(sess, vb->timestamp, offset);
	dev_dbg(core->dev, "esparser: ts = %llu pld_size = %u offset = %08X\n",
		vb->timestamp, payload_size, offset);

	pad_size = esparser_pad_start_code(vb);
	ret = esparser_write_data(core, phy, payload_size + pad_size);

	if (ret <= 0) {
		dev_warn(core->dev, "esparser: input parsing error\n");
		amvdec_remove_ts(sess, vb->timestamp);
		v4l2_m2m_buf_done(vbuf, VB2_BUF_STATE_ERROR);
		amvdec_write_parser(core, PARSER_FETCH_CMD, 0);

		return 0;
	}

	/* We need to wait until we parse the first keyframe.
	 * All buffers prior to the first keyframe must be dropped.
	 */
	if (!sess->keyframe_found)
		usleep_range(1000, 2000);

	if (sess->keyframe_found)
		atomic_inc(&sess->esparser_queued_bufs);
	else
		amvdec_remove_ts(sess, vb->timestamp);

	vbuf->flags = 0;
	vbuf->field = V4L2_FIELD_NONE;
	v4l2_m2m_buf_done(vbuf, VB2_BUF_STATE_DONE);

	return 0;
}