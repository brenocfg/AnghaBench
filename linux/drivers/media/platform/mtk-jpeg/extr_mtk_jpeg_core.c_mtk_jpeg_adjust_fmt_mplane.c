#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct v4l2_pix_format_mplane {int num_planes; TYPE_3__* plane_fmt; int /*<<< orphan*/  pixelformat; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct TYPE_4__ {struct v4l2_pix_format_mplane pix_mp; } ;
struct v4l2_format {int /*<<< orphan*/  type; TYPE_1__ fmt; } ;
struct mtk_jpeg_q_data {int /*<<< orphan*/ * sizeimage; int /*<<< orphan*/ * bytesperline; TYPE_2__* fmt; int /*<<< orphan*/  h; int /*<<< orphan*/  w; } ;
struct mtk_jpeg_ctx {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  sizeimage; int /*<<< orphan*/  bytesperline; } ;
struct TYPE_5__ {int colplanes; int /*<<< orphan*/  fourcc; } ;

/* Variables and functions */
 struct mtk_jpeg_q_data* mtk_jpeg_get_q_data (struct mtk_jpeg_ctx*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mtk_jpeg_adjust_fmt_mplane(struct mtk_jpeg_ctx *ctx,
				       struct v4l2_format *f)
{
	struct v4l2_pix_format_mplane *pix_mp = &f->fmt.pix_mp;
	struct mtk_jpeg_q_data *q_data;
	int i;

	q_data = mtk_jpeg_get_q_data(ctx, f->type);

	pix_mp->width = q_data->w;
	pix_mp->height = q_data->h;
	pix_mp->pixelformat = q_data->fmt->fourcc;
	pix_mp->num_planes = q_data->fmt->colplanes;

	for (i = 0; i < pix_mp->num_planes; i++) {
		pix_mp->plane_fmt[i].bytesperline = q_data->bytesperline[i];
		pix_mp->plane_fmt[i].sizeimage = q_data->sizeimage[i];
	}
}