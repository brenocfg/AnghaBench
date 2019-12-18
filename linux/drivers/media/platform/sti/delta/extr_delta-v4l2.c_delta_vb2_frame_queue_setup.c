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
struct vb2_queue {int dummy; } ;
struct device {int dummy; } ;
struct delta_streaminfo {scalar_t__ dpb; } ;
struct delta_frameinfo {unsigned int size; } ;
struct delta_dev {int /*<<< orphan*/  dev; } ;
struct delta_ctx {scalar_t__ nb_of_frames; int /*<<< orphan*/  name; struct delta_frameinfo frameinfo; struct delta_streaminfo streaminfo; struct delta_dev* dev; } ;

/* Variables and functions */
 unsigned int DELTA_MAX_FRAMES ; 
 unsigned int DELTA_MIN_FRAME_USER ; 
 scalar_t__ DELTA_PEAK_FRAME_SMOOTHING ; 
 int EINVAL ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,unsigned int,unsigned int) ; 
 struct delta_ctx* vb2_get_drv_priv (struct vb2_queue*) ; 

__attribute__((used)) static int delta_vb2_frame_queue_setup(struct vb2_queue *vq,
				       unsigned int *num_buffers,
				       unsigned int *num_planes,
				       unsigned int sizes[],
				       struct device *alloc_devs[])
{
	struct delta_ctx *ctx = vb2_get_drv_priv(vq);
	struct delta_dev *delta = ctx->dev;
	struct delta_streaminfo *streaminfo = &ctx->streaminfo;
	struct delta_frameinfo *frameinfo = &ctx->frameinfo;
	unsigned int size = frameinfo->size;

	/*
	 * the number of output buffers needed for decoding =
	 * user need (*num_buffers given, usually for display pipeline) +
	 * stream need (streaminfo->dpb) +
	 * decoding peak smoothing (depends on DELTA IP perf)
	 */
	if (*num_buffers < DELTA_MIN_FRAME_USER) {
		dev_dbg(delta->dev,
			"%s num_buffers too low (%d), increasing to %d\n",
			ctx->name, *num_buffers, DELTA_MIN_FRAME_USER);
		*num_buffers = DELTA_MIN_FRAME_USER;
	}

	*num_buffers += streaminfo->dpb + DELTA_PEAK_FRAME_SMOOTHING;

	if (*num_buffers > DELTA_MAX_FRAMES) {
		dev_dbg(delta->dev,
			"%s output frame count too high (%d), cut to %d\n",
			ctx->name, *num_buffers, DELTA_MAX_FRAMES);
		*num_buffers = DELTA_MAX_FRAMES;
	}

	if (*num_planes)
		return sizes[0] < size ? -EINVAL : 0;

	/* single plane for Y and CbCr */
	*num_planes = 1;

	sizes[0] = size;

	ctx->nb_of_frames = 0;

	return 0;
}