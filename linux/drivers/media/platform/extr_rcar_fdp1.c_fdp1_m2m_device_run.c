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
struct vb2_v4l2_buffer {int dummy; } ;
struct fdp1_field_buffer {int /*<<< orphan*/  last_field; } ;
struct fdp1_dev {int /*<<< orphan*/  m2m_dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  m2m_ctx; } ;
struct fdp1_ctx {scalar_t__ translen; TYPE_1__ fh; struct fdp1_dev* fdp1; } ;
struct fdp1_buffer {unsigned int num_fields; struct fdp1_field_buffer* fields; } ;

/* Variables and functions */
 int /*<<< orphan*/  dprintk (struct fdp1_dev*,char*,...) ; 
 int /*<<< orphan*/  fdp1_device_process (struct fdp1_ctx*) ; 
 scalar_t__ fdp1_prepare_job (struct fdp1_ctx*) ; 
 int /*<<< orphan*/  fdp1_queue_field (struct fdp1_ctx*,struct fdp1_field_buffer*) ; 
 struct fdp1_buffer* to_fdp1_buffer (struct vb2_v4l2_buffer*) ; 
 int /*<<< orphan*/  v4l2_m2m_job_finish (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct vb2_v4l2_buffer* v4l2_m2m_src_buf_remove (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void fdp1_m2m_device_run(void *priv)
{
	struct fdp1_ctx *ctx = priv;
	struct fdp1_dev *fdp1 = ctx->fdp1;
	struct vb2_v4l2_buffer *src_vb;
	struct fdp1_buffer *buf;
	unsigned int i;

	dprintk(fdp1, "+\n");

	ctx->translen = 0;

	/* Get our incoming buffer of either one or two fields, or one frame */
	src_vb = v4l2_m2m_src_buf_remove(ctx->fh.m2m_ctx);
	buf = to_fdp1_buffer(src_vb);

	for (i = 0; i < buf->num_fields; i++) {
		struct fdp1_field_buffer *fbuf = &buf->fields[i];

		fdp1_queue_field(ctx, fbuf);
		dprintk(fdp1, "Queued Buffer [%d] last_field:%d\n",
			i, fbuf->last_field);
	}

	/* Queue as many jobs as our data provides for */
	while (fdp1_prepare_job(ctx))
		;

	if (ctx->translen == 0) {
		dprintk(fdp1, "No jobs were processed. M2M action complete\n");
		v4l2_m2m_job_finish(fdp1->m2m_dev, ctx->fh.m2m_ctx);
		return;
	}

	/* Kick the job processing action */
	fdp1_device_process(ctx);
}