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
typedef  int u32 ;
struct v4l2_pix_format_mplane {int height; int width; int pixelformat; TYPE_1__* plane_fmt; } ;
struct ceu_mbus_fmt {int bpp; int fmt_order_swap; int fmt_order; int /*<<< orphan*/  swapped; } ;
struct ceu_subdev {unsigned int mbus_flags; struct ceu_mbus_fmt mbus_fmt; } ;
struct ceu_device {struct ceu_subdev* sd; struct v4l2_pix_format_mplane v4l2_pix; } ;
struct TYPE_2__ {int bytesperline; } ;

/* Variables and functions */
 int /*<<< orphan*/  CEU_CAIFR ; 
 int /*<<< orphan*/  CEU_CAMCR ; 
 int CEU_CAMCR_JPEG ; 
 int /*<<< orphan*/  CEU_CAMOR ; 
 int /*<<< orphan*/  CEU_CAPCR ; 
 int CEU_CAPCR_BUS_WIDTH256 ; 
 int /*<<< orphan*/  CEU_CAPWR ; 
 int /*<<< orphan*/  CEU_CDOCR ; 
 int CEU_CDOCR_NO_DOWSAMPLE ; 
 int CEU_CDOCR_SWAP_ENDIANNESS ; 
 int /*<<< orphan*/  CEU_CDWDR ; 
 int /*<<< orphan*/  CEU_CFSZR ; 
 int /*<<< orphan*/  CEU_CFWCR ; 
 int /*<<< orphan*/  CEU_CRCMPR ; 
 int /*<<< orphan*/  CEU_CRCNTR ; 
 int EINVAL ; 
 unsigned int V4L2_MBUS_HSYNC_ACTIVE_LOW ; 
 unsigned int V4L2_MBUS_VSYNC_ACTIVE_LOW ; 
#define  V4L2_PIX_FMT_NV12 135 
#define  V4L2_PIX_FMT_NV16 134 
#define  V4L2_PIX_FMT_NV21 133 
#define  V4L2_PIX_FMT_NV61 132 
#define  V4L2_PIX_FMT_UYVY 131 
#define  V4L2_PIX_FMT_VYUY 130 
#define  V4L2_PIX_FMT_YUYV 129 
#define  V4L2_PIX_FMT_YVYU 128 
 int /*<<< orphan*/  ceu_write (struct ceu_device*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ceu_hw_config(struct ceu_device *ceudev)
{
	u32 camcr, cdocr, cfzsr, cdwdr, capwr;
	struct v4l2_pix_format_mplane *pix = &ceudev->v4l2_pix;
	struct ceu_subdev *ceu_sd = ceudev->sd;
	struct ceu_mbus_fmt *mbus_fmt = &ceu_sd->mbus_fmt;
	unsigned int mbus_flags = ceu_sd->mbus_flags;

	/* Start configuring CEU registers */
	ceu_write(ceudev, CEU_CAIFR, 0);
	ceu_write(ceudev, CEU_CFWCR, 0);
	ceu_write(ceudev, CEU_CRCNTR, 0);
	ceu_write(ceudev, CEU_CRCMPR, 0);

	/* Set the frame capture period for both image capture and data sync. */
	capwr = (pix->height << 16) | pix->width * mbus_fmt->bpp / 8;

	/*
	 * Swap input data endianness by default.
	 * In data fetch mode bytes are received in chunks of 8 bytes.
	 * D0, D1, D2, D3, D4, D5, D6, D7 (D0 received first)
	 * The data is however by default written to memory in reverse order:
	 * D7, D6, D5, D4, D3, D2, D1, D0 (D7 written to lowest byte)
	 *
	 * Use CEU_CDOCR[2:0] to swap data ordering.
	 */
	cdocr = CEU_CDOCR_SWAP_ENDIANNESS;

	/*
	 * Configure CAMCR and CDOCR:
	 * match input components ordering with memory output format and
	 * handle downsampling to YUV420.
	 *
	 * If the memory output planar format is 'swapped' (Cr before Cb) and
	 * input format is not, use the swapped version of CAMCR.DTARY.
	 *
	 * If the memory output planar format is not 'swapped' (Cb before Cr)
	 * and input format is, use the swapped version of CAMCR.DTARY.
	 *
	 * CEU by default downsample to planar YUV420 (CDCOR[4] = 0).
	 * If output is planar YUV422 set CDOCR[4] = 1
	 *
	 * No downsample for data fetch sync mode.
	 */
	switch (pix->pixelformat) {
	/* Data fetch sync mode */
	case V4L2_PIX_FMT_YUYV:
	case V4L2_PIX_FMT_YVYU:
	case V4L2_PIX_FMT_UYVY:
	case V4L2_PIX_FMT_VYUY:
		camcr	= CEU_CAMCR_JPEG;
		cdocr	|= CEU_CDOCR_NO_DOWSAMPLE;
		cfzsr	= (pix->height << 16) | pix->width;
		cdwdr	= pix->plane_fmt[0].bytesperline;
		break;

	/* Non-swapped planar image capture mode. */
	case V4L2_PIX_FMT_NV16:
		cdocr	|= CEU_CDOCR_NO_DOWSAMPLE;
		/* fall-through */
	case V4L2_PIX_FMT_NV12:
		if (mbus_fmt->swapped)
			camcr = mbus_fmt->fmt_order_swap;
		else
			camcr = mbus_fmt->fmt_order;

		cfzsr	= (pix->height << 16) | pix->width;
		cdwdr	= pix->width;
		break;

	/* Swapped planar image capture mode. */
	case V4L2_PIX_FMT_NV61:
		cdocr	|= CEU_CDOCR_NO_DOWSAMPLE;
		/* fall-through */
	case V4L2_PIX_FMT_NV21:
		if (mbus_fmt->swapped)
			camcr = mbus_fmt->fmt_order;
		else
			camcr = mbus_fmt->fmt_order_swap;

		cfzsr	= (pix->height << 16) | pix->width;
		cdwdr	= pix->width;
		break;

	default:
		return -EINVAL;
	}

	camcr |= mbus_flags & V4L2_MBUS_VSYNC_ACTIVE_LOW ? 1 << 1 : 0;
	camcr |= mbus_flags & V4L2_MBUS_HSYNC_ACTIVE_LOW ? 1 << 0 : 0;

	/* TODO: handle 16 bit bus width with DTIF bit in CAMCR */
	ceu_write(ceudev, CEU_CAMCR, camcr);
	ceu_write(ceudev, CEU_CDOCR, cdocr);
	ceu_write(ceudev, CEU_CAPCR, CEU_CAPCR_BUS_WIDTH256);

	/*
	 * TODO: make CAMOR offsets configurable.
	 * CAMOR wants to know the number of blanks between a VS/HS signal
	 * and valid data. This value should actually come from the sensor...
	 */
	ceu_write(ceudev, CEU_CAMOR, 0);

	/* TODO: 16 bit bus width require re-calculation of cdwdr and cfzsr */
	ceu_write(ceudev, CEU_CAPWR, capwr);
	ceu_write(ceudev, CEU_CFSZR, cfzsr);
	ceu_write(ceudev, CEU_CDWDR, cdwdr);

	return 0;
}