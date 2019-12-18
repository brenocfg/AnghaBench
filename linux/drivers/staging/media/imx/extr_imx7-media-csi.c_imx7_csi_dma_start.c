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
struct v4l2_pix_format {int /*<<< orphan*/  sizeimage; } ;
struct TYPE_3__ {struct v4l2_pix_format pix; } ;
struct TYPE_4__ {TYPE_1__ fmt; } ;
struct imx_media_video_dev {TYPE_2__ fmt; } ;
struct imx7_csi {int last_eof; int /*<<< orphan*/  last_eof_completion; scalar_t__ frame_sequence; int /*<<< orphan*/  sd; int /*<<< orphan*/  underrun_buf; int /*<<< orphan*/  dev; struct imx_media_video_dev* vdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  imx7_csi_setup_vb2_buf (struct imx7_csi*) ; 
 int imx_media_alloc_dma_buf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_warn (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static int imx7_csi_dma_start(struct imx7_csi *csi)
{
	struct imx_media_video_dev *vdev = csi->vdev;
	struct v4l2_pix_format *out_pix = &vdev->fmt.fmt.pix;
	int ret;

	ret = imx_media_alloc_dma_buf(csi->dev, &csi->underrun_buf,
				      out_pix->sizeimage);
	if (ret < 0) {
		v4l2_warn(&csi->sd, "consider increasing the CMA area\n");
		return ret;
	}

	csi->frame_sequence = 0;
	csi->last_eof = false;
	init_completion(&csi->last_eof_completion);

	imx7_csi_setup_vb2_buf(csi);

	return 0;
}