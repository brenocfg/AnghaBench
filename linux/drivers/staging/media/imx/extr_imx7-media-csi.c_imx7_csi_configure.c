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
typedef  int u32 ;
struct v4l2_pix_format {int width; scalar_t__ field; int pixelformat; int /*<<< orphan*/  height; } ;
struct TYPE_4__ {struct v4l2_pix_format pix; } ;
struct TYPE_5__ {TYPE_1__ fmt; } ;
struct imx_media_video_dev {TYPE_2__ fmt; } ;
struct imx7_csi {int /*<<< orphan*/  is_csi2; TYPE_3__* format_mbus; struct imx_media_video_dev* vdev; } ;
typedef  int /*<<< orphan*/  __u32 ;
struct TYPE_6__ {int /*<<< orphan*/  code; } ;

/* Variables and functions */
 int BIT_BASEADDR_CHG_ERR_EN ; 
 int BIT_BASEADDR_SWITCH_EN ; 
 int BIT_BASEADDR_SWITCH_SEL ; 
 int BIT_DATA_FROM_MIPI ; 
 int BIT_GCLK_MODE ; 
 int BIT_MIPI_DATA_FORMAT_MASK ; 
 int BIT_MIPI_DATA_FORMAT_RAW10 ; 
 int BIT_MIPI_DATA_FORMAT_RAW12 ; 
 int BIT_MIPI_DATA_FORMAT_RAW14 ; 
 int BIT_MIPI_DATA_FORMAT_RAW8 ; 
 int BIT_MIPI_DATA_FORMAT_YUV422_8B ; 
 int BIT_PIXEL_BIT ; 
 int /*<<< orphan*/  CSI_CSICR1 ; 
 int /*<<< orphan*/  CSI_CSICR18 ; 
 int EINVAL ; 
 size_t IMX7_CSI_PAD_SINK ; 
 int /*<<< orphan*/  MEDIA_BUS_FMT_SBGGR10_1X10 ; 
 int /*<<< orphan*/  MEDIA_BUS_FMT_SBGGR12_1X12 ; 
 int /*<<< orphan*/  MEDIA_BUS_FMT_SBGGR14_1X14 ; 
 scalar_t__ V4L2_FIELD_INTERLACED ; 
#define  V4L2_PIX_FMT_SBGGR16 131 
#define  V4L2_PIX_FMT_SBGGR8 130 
#define  V4L2_PIX_FMT_UYVY 129 
#define  V4L2_PIX_FMT_YUYV 128 
 int /*<<< orphan*/  imx7_csi_buf_stride_set (struct imx7_csi*,int) ; 
 int /*<<< orphan*/  imx7_csi_deinterlace_enable (struct imx7_csi*,int) ; 
 int imx7_csi_reg_read (struct imx7_csi*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  imx7_csi_reg_write (struct imx7_csi*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  imx7_csi_set_imagpara (struct imx7_csi*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int imx7_csi_configure(struct imx7_csi *csi)
{
	struct imx_media_video_dev *vdev = csi->vdev;
	struct v4l2_pix_format *out_pix = &vdev->fmt.fmt.pix;
	__u32 in_code = csi->format_mbus[IMX7_CSI_PAD_SINK].code;
	u32 cr1, cr18;
	int width = out_pix->width;

	if (out_pix->field == V4L2_FIELD_INTERLACED) {
		imx7_csi_deinterlace_enable(csi, true);
		imx7_csi_buf_stride_set(csi, out_pix->width);
	} else {
		imx7_csi_deinterlace_enable(csi, false);
		imx7_csi_buf_stride_set(csi, 0);
	}

	cr18 = imx7_csi_reg_read(csi, CSI_CSICR18);

	if (!csi->is_csi2) {
		if (out_pix->pixelformat == V4L2_PIX_FMT_UYVY ||
		    out_pix->pixelformat == V4L2_PIX_FMT_YUYV)
			width *= 2;

		imx7_csi_set_imagpara(csi, width, out_pix->height);

		cr18 |= (BIT_BASEADDR_SWITCH_EN | BIT_BASEADDR_SWITCH_SEL |
			BIT_BASEADDR_CHG_ERR_EN);
		imx7_csi_reg_write(csi, cr18, CSI_CSICR18);

		return 0;
	}

	imx7_csi_set_imagpara(csi, width, out_pix->height);

	cr1 = imx7_csi_reg_read(csi, CSI_CSICR1);
	cr1 &= ~BIT_GCLK_MODE;

	cr18 &= BIT_MIPI_DATA_FORMAT_MASK;
	cr18 |= BIT_DATA_FROM_MIPI;

	switch (out_pix->pixelformat) {
	case V4L2_PIX_FMT_UYVY:
	case V4L2_PIX_FMT_YUYV:
		cr18 |= BIT_MIPI_DATA_FORMAT_YUV422_8B;
		break;
	case V4L2_PIX_FMT_SBGGR8:
		cr18 |= BIT_MIPI_DATA_FORMAT_RAW8;
		break;
	case V4L2_PIX_FMT_SBGGR16:
		if (in_code == MEDIA_BUS_FMT_SBGGR10_1X10)
			cr18 |= BIT_MIPI_DATA_FORMAT_RAW10;
		else if (in_code == MEDIA_BUS_FMT_SBGGR12_1X12)
			cr18 |= BIT_MIPI_DATA_FORMAT_RAW12;
		else if (in_code == MEDIA_BUS_FMT_SBGGR14_1X14)
			cr18 |= BIT_MIPI_DATA_FORMAT_RAW14;
		cr1 |= BIT_PIXEL_BIT;
		break;
	default:
		return -EINVAL;
	}

	imx7_csi_reg_write(csi, cr1, CSI_CSICR1);
	imx7_csi_reg_write(csi, cr18, CSI_CSICR18);

	return 0;
}