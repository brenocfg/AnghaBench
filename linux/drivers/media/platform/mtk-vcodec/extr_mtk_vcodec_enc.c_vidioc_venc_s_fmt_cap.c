#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct vb2_queue {int dummy; } ;
struct v4l2_plane_pix_format {int /*<<< orphan*/  sizeimage; int /*<<< orphan*/  bytesperline; } ;
struct TYPE_6__ {int num_planes; struct v4l2_plane_pix_format* plane_fmt; int /*<<< orphan*/  field; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct TYPE_5__ {int /*<<< orphan*/  pixelformat; } ;
struct TYPE_7__ {TYPE_2__ pix_mp; TYPE_1__ pix; } ;
struct v4l2_format {TYPE_3__ fmt; int /*<<< orphan*/  type; } ;
struct mtk_video_fmt {int /*<<< orphan*/  fourcc; } ;
struct mtk_vcodec_ctx {scalar_t__ state; int /*<<< orphan*/  m2m_ctx; } ;
struct mtk_q_data {struct mtk_video_fmt const* fmt; int /*<<< orphan*/ * sizeimage; int /*<<< orphan*/ * bytesperline; int /*<<< orphan*/  field; int /*<<< orphan*/  coded_height; int /*<<< orphan*/  coded_width; } ;
struct file {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/  fourcc; } ;

/* Variables and functions */
 size_t CAP_FMT_IDX ; 
 int EBUSY ; 
 int EINVAL ; 
 scalar_t__ MTK_STATE_FREE ; 
 scalar_t__ MTK_STATE_INIT ; 
 struct mtk_vcodec_ctx* fh_to_ctx (void*) ; 
 int /*<<< orphan*/  mtk_v4l2_err (char*,...) ; 
 struct mtk_video_fmt* mtk_venc_find_format (struct v4l2_format*) ; 
 struct mtk_q_data* mtk_venc_get_q_data (struct mtk_vcodec_ctx*,int /*<<< orphan*/ ) ; 
 TYPE_4__* mtk_video_formats ; 
 struct vb2_queue* v4l2_m2m_get_vq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ vb2_is_busy (struct vb2_queue*) ; 
 int venc_if_init (struct mtk_vcodec_ctx*,int /*<<< orphan*/ ) ; 
 int vidioc_try_fmt (struct v4l2_format*,struct mtk_video_fmt const*) ; 

__attribute__((used)) static int vidioc_venc_s_fmt_cap(struct file *file, void *priv,
			     struct v4l2_format *f)
{
	struct mtk_vcodec_ctx *ctx = fh_to_ctx(priv);
	struct vb2_queue *vq;
	struct mtk_q_data *q_data;
	int i, ret;
	const struct mtk_video_fmt *fmt;

	vq = v4l2_m2m_get_vq(ctx->m2m_ctx, f->type);
	if (!vq) {
		mtk_v4l2_err("fail to get vq");
		return -EINVAL;
	}

	if (vb2_is_busy(vq)) {
		mtk_v4l2_err("queue busy");
		return -EBUSY;
	}

	q_data = mtk_venc_get_q_data(ctx, f->type);
	if (!q_data) {
		mtk_v4l2_err("fail to get q data");
		return -EINVAL;
	}

	fmt = mtk_venc_find_format(f);
	if (!fmt) {
		f->fmt.pix.pixelformat = mtk_video_formats[CAP_FMT_IDX].fourcc;
		fmt = mtk_venc_find_format(f);
	}

	q_data->fmt = fmt;
	ret = vidioc_try_fmt(f, q_data->fmt);
	if (ret)
		return ret;

	q_data->coded_width = f->fmt.pix_mp.width;
	q_data->coded_height = f->fmt.pix_mp.height;
	q_data->field = f->fmt.pix_mp.field;

	for (i = 0; i < f->fmt.pix_mp.num_planes; i++) {
		struct v4l2_plane_pix_format	*plane_fmt;

		plane_fmt = &f->fmt.pix_mp.plane_fmt[i];
		q_data->bytesperline[i]	= plane_fmt->bytesperline;
		q_data->sizeimage[i] = plane_fmt->sizeimage;
	}

	if (ctx->state == MTK_STATE_FREE) {
		ret = venc_if_init(ctx, q_data->fmt->fourcc);
		if (ret) {
			mtk_v4l2_err("venc_if_init failed=%d, codec type=%x",
					ret, q_data->fmt->fourcc);
			return -EBUSY;
		}
		ctx->state = MTK_STATE_INIT;
	}

	return 0;
}