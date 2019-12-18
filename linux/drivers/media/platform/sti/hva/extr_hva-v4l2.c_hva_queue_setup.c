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
struct vb2_queue {scalar_t__ type; } ;
struct TYPE_2__ {unsigned int size; } ;
struct hva_ctx {unsigned int max_stream_size; TYPE_1__ frameinfo; int /*<<< orphan*/  name; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ V4L2_BUF_TYPE_VIDEO_OUTPUT ; 
 struct device* ctx_to_dev (struct hva_ctx*) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  to_type_str (scalar_t__) ; 
 struct hva_ctx* vb2_get_drv_priv (struct vb2_queue*) ; 

__attribute__((used)) static int hva_queue_setup(struct vb2_queue *vq,
			   unsigned int *num_buffers, unsigned int *num_planes,
			   unsigned int sizes[], struct device *alloc_devs[])
{
	struct hva_ctx *ctx = vb2_get_drv_priv(vq);
	struct device *dev = ctx_to_dev(ctx);
	unsigned int size;

	dev_dbg(dev, "%s %s queue setup: num_buffers %d\n", ctx->name,
		to_type_str(vq->type), *num_buffers);

	size = vq->type == V4L2_BUF_TYPE_VIDEO_OUTPUT ?
		ctx->frameinfo.size : ctx->max_stream_size;

	if (*num_planes)
		return sizes[0] < size ? -EINVAL : 0;

	/* only one plane supported */
	*num_planes = 1;
	sizes[0] = size;

	return 0;
}