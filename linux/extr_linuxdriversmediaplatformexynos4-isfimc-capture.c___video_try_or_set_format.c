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
struct v4l2_subdev {int dummy; } ;
struct v4l2_pix_format_mplane {unsigned int width; unsigned int height; int /*<<< orphan*/  plane_fmt; int /*<<< orphan*/  pixelformat; } ;
struct v4l2_mbus_framefmt {unsigned int width; unsigned int height; int /*<<< orphan*/  code; } ;
struct TYPE_3__ {struct v4l2_pix_format_mplane pix_mp; } ;
struct v4l2_format {TYPE_1__ fmt; } ;
struct exynos_video_entity {int /*<<< orphan*/  pipe; } ;
struct fimc_vid_cap {struct v4l2_mbus_framefmt ci_fmt; int /*<<< orphan*/  user_subdev_api; struct fimc_ctx* ctx; struct exynos_video_entity ve; } ;
struct fimc_fmt {int flags; int /*<<< orphan*/  memplanes; int /*<<< orphan*/  mbus_code; } ;
struct fimc_dev {struct fimc_vid_cap vid_cap; } ;
struct TYPE_4__ {unsigned int f_width; unsigned int f_height; } ;
struct fimc_ctx {TYPE_2__ s_frame; } ;

/* Variables and functions */
 int EINVAL ; 
 int EPIPE ; 
 int /*<<< orphan*/  FIMC_SD_PAD_SINK_CAM ; 
 int /*<<< orphan*/  FIMC_SD_PAD_SOURCE ; 
 int FMT_FLAGS_COMPRESSED ; 
 int /*<<< orphan*/  IDX_SENSOR ; 
 struct v4l2_subdev* __fimc_md_get_subdev (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fimc_adjust_mplane_format (struct fimc_fmt*,unsigned int,unsigned int,struct v4l2_pix_format_mplane*) ; 
 struct fimc_fmt* fimc_capture_try_format (struct fimc_ctx*,unsigned int*,unsigned int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fimc_get_sensor_frame_desc (struct v4l2_subdev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ fimc_jpeg_fourcc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fimc_md_graph_lock (struct exynos_video_entity*) ; 
 int /*<<< orphan*/  fimc_md_graph_unlock (struct exynos_video_entity*) ; 
 int fimc_pipeline_try_format (struct fimc_ctx*,struct v4l2_mbus_framefmt*,struct fimc_fmt**,int) ; 

__attribute__((used)) static int __video_try_or_set_format(struct fimc_dev *fimc,
				     struct v4l2_format *f, bool try,
				     struct fimc_fmt **inp_fmt,
				     struct fimc_fmt **out_fmt)
{
	struct v4l2_pix_format_mplane *pix = &f->fmt.pix_mp;
	struct fimc_vid_cap *vc = &fimc->vid_cap;
	struct exynos_video_entity *ve = &vc->ve;
	struct fimc_ctx *ctx = vc->ctx;
	unsigned int width = 0, height = 0;
	int ret = 0;

	/* Pre-configure format at the camera input interface, for JPEG only */
	if (fimc_jpeg_fourcc(pix->pixelformat)) {
		fimc_capture_try_format(ctx, &pix->width, &pix->height,
					NULL, &pix->pixelformat,
					FIMC_SD_PAD_SINK_CAM);
		if (try) {
			width = pix->width;
			height = pix->height;
		} else {
			ctx->s_frame.f_width = pix->width;
			ctx->s_frame.f_height = pix->height;
		}
	}

	/* Try the format at the scaler and the DMA output */
	*out_fmt = fimc_capture_try_format(ctx, &pix->width, &pix->height,
					  NULL, &pix->pixelformat,
					  FIMC_SD_PAD_SOURCE);
	if (*out_fmt == NULL)
		return -EINVAL;

	/* Restore image width/height for JPEG (no resizing supported). */
	if (try && fimc_jpeg_fourcc(pix->pixelformat)) {
		pix->width = width;
		pix->height = height;
	}

	/* Try to match format at the host and the sensor */
	if (!vc->user_subdev_api) {
		struct v4l2_mbus_framefmt mbus_fmt;
		struct v4l2_mbus_framefmt *mf;

		mf = try ? &mbus_fmt : &fimc->vid_cap.ci_fmt;

		mf->code = (*out_fmt)->mbus_code;
		mf->width = pix->width;
		mf->height = pix->height;

		fimc_md_graph_lock(ve);
		ret = fimc_pipeline_try_format(ctx, mf, inp_fmt, try);
		fimc_md_graph_unlock(ve);

		if (ret < 0)
			return ret;

		pix->width = mf->width;
		pix->height = mf->height;
	}

	fimc_adjust_mplane_format(*out_fmt, pix->width, pix->height, pix);

	if ((*out_fmt)->flags & FMT_FLAGS_COMPRESSED) {
		struct v4l2_subdev *sensor;

		fimc_md_graph_lock(ve);

		sensor = __fimc_md_get_subdev(ve->pipe, IDX_SENSOR);
		if (sensor)
			fimc_get_sensor_frame_desc(sensor, pix->plane_fmt,
						   (*out_fmt)->memplanes, try);
		else
			ret = -EPIPE;

		fimc_md_graph_unlock(ve);
	}

	return ret;
}