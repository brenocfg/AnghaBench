#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct vb2_v4l2_buffer {int dummy; } ;
struct vb2_queue {scalar_t__ type; } ;
struct hva_dev {int /*<<< orphan*/  nb_of_instances; struct hva_ctx** instances; } ;
struct TYPE_12__ {TYPE_6__* m2m_ctx; } ;
struct TYPE_11__ {int /*<<< orphan*/  pixelformat; } ;
struct TYPE_10__ {int /*<<< orphan*/  streamformat; } ;
struct hva_ctx {unsigned int id; int /*<<< orphan*/  sys_errors; TYPE_5__ fh; int /*<<< orphan*/  enc; TYPE_4__ frameinfo; TYPE_3__ streaminfo; int /*<<< orphan*/  name; } ;
struct device {int dummy; } ;
struct TYPE_9__ {int /*<<< orphan*/  q; } ;
struct TYPE_8__ {int /*<<< orphan*/  q; } ;
struct TYPE_13__ {TYPE_2__ out_q_ctx; TYPE_1__ cap_q_ctx; } ;

/* Variables and functions */
 int ENOMEM ; 
 unsigned int HVA_MAX_INSTANCES ; 
 scalar_t__ V4L2_BUF_TYPE_VIDEO_OUTPUT ; 
 scalar_t__ V4L2_TYPE_IS_OUTPUT (scalar_t__) ; 
 int /*<<< orphan*/  VB2_BUF_STATE_QUEUED ; 
 struct device* ctx_to_dev (struct hva_ctx*) ; 
 struct hva_dev* ctx_to_hdev (struct hva_ctx*) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int /*<<< orphan*/ ) ; 
 int hva_open_encoder (struct hva_ctx*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  to_type_str (scalar_t__) ; 
 int /*<<< orphan*/  v4l2_m2m_buf_done (struct vb2_v4l2_buffer*,int /*<<< orphan*/ ) ; 
 struct vb2_v4l2_buffer* v4l2_m2m_dst_buf_remove (TYPE_6__*) ; 
 struct vb2_v4l2_buffer* v4l2_m2m_src_buf_remove (TYPE_6__*) ; 
 struct hva_ctx* vb2_get_drv_priv (struct vb2_queue*) ; 
 int /*<<< orphan*/  vb2_start_streaming_called (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int hva_start_streaming(struct vb2_queue *vq, unsigned int count)
{
	struct hva_ctx *ctx = vb2_get_drv_priv(vq);
	struct hva_dev *hva = ctx_to_hdev(ctx);
	struct device *dev = ctx_to_dev(ctx);
	struct vb2_v4l2_buffer *vbuf;
	int ret;
	unsigned int i;
	bool found = false;

	dev_dbg(dev, "%s %s start streaming\n", ctx->name,
		to_type_str(vq->type));

	/* open encoder when both start_streaming have been called */
	if (V4L2_TYPE_IS_OUTPUT(vq->type)) {
		if (!vb2_start_streaming_called(&ctx->fh.m2m_ctx->cap_q_ctx.q))
			return 0;
	} else {
		if (!vb2_start_streaming_called(&ctx->fh.m2m_ctx->out_q_ctx.q))
			return 0;
	}

	/* store the instance context in the instances array */
	for (i = 0; i < HVA_MAX_INSTANCES; i++) {
		if (!hva->instances[i]) {
			hva->instances[i] = ctx;
			/* save the context identifier in the context */
			ctx->id = i;
			found = true;
			break;
		}
	}

	if (!found) {
		dev_err(dev, "%s maximum instances reached\n", ctx->name);
		ret = -ENOMEM;
		goto err;
	}

	hva->nb_of_instances++;

	if (!ctx->enc) {
		ret = hva_open_encoder(ctx,
				       ctx->streaminfo.streamformat,
				       ctx->frameinfo.pixelformat,
				       &ctx->enc);
		if (ret < 0)
			goto err_ctx;
	}

	return 0;

err_ctx:
	hva->instances[ctx->id] = NULL;
	hva->nb_of_instances--;
err:
	if (vq->type == V4L2_BUF_TYPE_VIDEO_OUTPUT) {
		/* return of all pending buffers to vb2 (in queued state) */
		while ((vbuf = v4l2_m2m_src_buf_remove(ctx->fh.m2m_ctx)))
			v4l2_m2m_buf_done(vbuf, VB2_BUF_STATE_QUEUED);
	} else {
		/* return of all pending buffers to vb2 (in queued state) */
		while ((vbuf = v4l2_m2m_dst_buf_remove(ctx->fh.m2m_ctx)))
			v4l2_m2m_buf_done(vbuf, VB2_BUF_STATE_QUEUED);
	}

	ctx->sys_errors++;

	return ret;
}