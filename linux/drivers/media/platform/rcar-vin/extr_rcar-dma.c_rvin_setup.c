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
struct TYPE_5__ {int field; int pixelformat; int width; int height; } ;
struct rvin_dev {int std; int mbus_code; scalar_t__ is_csi; TYPE_3__* info; TYPE_2__ format; int /*<<< orphan*/  alpha; TYPE_1__* parallel; } ;
struct TYPE_6__ {scalar_t__ model; int /*<<< orphan*/  use_mc; } ;
struct TYPE_4__ {int mbus_flags; int /*<<< orphan*/  mbus_type; } ;

/* Variables and functions */
 int ALIGN (int,int) ; 
 int EINVAL ; 
#define  MEDIA_BUS_FMT_RGB888_1X24 146 
#define  MEDIA_BUS_FMT_UYVY10_2X10 145 
#define  MEDIA_BUS_FMT_UYVY8_1X16 144 
#define  MEDIA_BUS_FMT_UYVY8_2X8 143 
#define  MEDIA_BUS_FMT_YUYV8_1X16 142 
 scalar_t__ RCAR_GEN3 ; 
#define  V4L2_FIELD_BOTTOM 141 
#define  V4L2_FIELD_INTERLACED 140 
#define  V4L2_FIELD_INTERLACED_BT 139 
#define  V4L2_FIELD_INTERLACED_TB 138 
#define  V4L2_FIELD_NONE 137 
#define  V4L2_FIELD_TOP 136 
 int /*<<< orphan*/  V4L2_MBUS_BT656 ; 
 int V4L2_MBUS_DATA_ENABLE_LOW ; 
 int V4L2_MBUS_HSYNC_ACTIVE_LOW ; 
 int V4L2_MBUS_VSYNC_ACTIVE_LOW ; 
#define  V4L2_PIX_FMT_ABGR32 135 
#define  V4L2_PIX_FMT_ARGB555 134 
#define  V4L2_PIX_FMT_NV16 133 
#define  V4L2_PIX_FMT_RGB565 132 
#define  V4L2_PIX_FMT_UYVY 131 
#define  V4L2_PIX_FMT_XBGR32 130 
#define  V4L2_PIX_FMT_XRGB555 129 
#define  V4L2_PIX_FMT_YUYV 128 
 int V4L2_STD_525_60 ; 
 int VNDMR2_CES ; 
 int VNDMR2_FTEV ; 
 int VNDMR2_HPS ; 
 int /*<<< orphan*/  VNDMR2_REG ; 
 int VNDMR2_VLV (int) ; 
 int VNDMR2_VPS ; 
 int VNDMR_A8BIT (int /*<<< orphan*/ ) ; 
 int VNDMR_ABIT ; 
 int VNDMR_BPSM ; 
 int VNDMR_DTMD_ARGB ; 
 int VNDMR_DTMD_YCSEP ; 
 int VNDMR_EXRGB ; 
 int /*<<< orphan*/  VNDMR_REG ; 
 int VNIE_EFE ; 
 int VNIE_FIE ; 
 int /*<<< orphan*/  VNIE_REG ; 
 int /*<<< orphan*/  VNINTS_REG ; 
 int VNMC_BPS ; 
 int VNMC_DPINE ; 
 int VNMC_FOC ; 
 int VNMC_IM_EVEN ; 
 int VNMC_IM_FULL ; 
 int VNMC_IM_ODD ; 
 int VNMC_IM_ODD_EVEN ; 
 int VNMC_INF_RGB888 ; 
 int VNMC_INF_YUV10_BT601 ; 
 int VNMC_INF_YUV10_BT656 ; 
 int VNMC_INF_YUV16 ; 
 int VNMC_INF_YUV8_BT601 ; 
 int VNMC_INF_YUV8_BT656 ; 
 int VNMC_ME ; 
 int /*<<< orphan*/  VNMC_REG ; 
 int VNMC_VUP ; 
 int VNMC_YCAL ; 
 int /*<<< orphan*/  VNUVAOF_REG ; 
 int /*<<< orphan*/  rvin_write (struct rvin_dev*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vin_err (struct rvin_dev*,char*,int) ; 

__attribute__((used)) static int rvin_setup(struct rvin_dev *vin)
{
	u32 vnmc, dmr, dmr2, interrupts;
	bool progressive = false, output_is_yuv = false, input_is_yuv = false;

	switch (vin->format.field) {
	case V4L2_FIELD_TOP:
		vnmc = VNMC_IM_ODD;
		break;
	case V4L2_FIELD_BOTTOM:
		vnmc = VNMC_IM_EVEN;
		break;
	case V4L2_FIELD_INTERLACED:
		/* Default to TB */
		vnmc = VNMC_IM_FULL;
		/* Use BT if video standard can be read and is 60 Hz format */
		if (!vin->info->use_mc && vin->std & V4L2_STD_525_60)
			vnmc = VNMC_IM_FULL | VNMC_FOC;
		break;
	case V4L2_FIELD_INTERLACED_TB:
		vnmc = VNMC_IM_FULL;
		break;
	case V4L2_FIELD_INTERLACED_BT:
		vnmc = VNMC_IM_FULL | VNMC_FOC;
		break;
	case V4L2_FIELD_NONE:
		vnmc = VNMC_IM_ODD_EVEN;
		progressive = true;
		break;
	default:
		vnmc = VNMC_IM_ODD;
		break;
	}

	/*
	 * Input interface
	 */
	switch (vin->mbus_code) {
	case MEDIA_BUS_FMT_YUYV8_1X16:
		/* BT.601/BT.1358 16bit YCbCr422 */
		vnmc |= VNMC_INF_YUV16;
		input_is_yuv = true;
		break;
	case MEDIA_BUS_FMT_UYVY8_1X16:
		vnmc |= VNMC_INF_YUV16 | VNMC_YCAL;
		input_is_yuv = true;
		break;
	case MEDIA_BUS_FMT_UYVY8_2X8:
		/* BT.656 8bit YCbCr422 or BT.601 8bit YCbCr422 */
		if (!vin->is_csi &&
		    vin->parallel->mbus_type == V4L2_MBUS_BT656)
			vnmc |= VNMC_INF_YUV8_BT656;
		else
			vnmc |= VNMC_INF_YUV8_BT601;

		input_is_yuv = true;
		break;
	case MEDIA_BUS_FMT_RGB888_1X24:
		vnmc |= VNMC_INF_RGB888;
		break;
	case MEDIA_BUS_FMT_UYVY10_2X10:
		/* BT.656 10bit YCbCr422 or BT.601 10bit YCbCr422 */
		if (!vin->is_csi &&
		    vin->parallel->mbus_type == V4L2_MBUS_BT656)
			vnmc |= VNMC_INF_YUV10_BT656;
		else
			vnmc |= VNMC_INF_YUV10_BT601;

		input_is_yuv = true;
		break;
	default:
		break;
	}

	/* Enable VSYNC Field Toggle mode after one VSYNC input */
	if (vin->info->model == RCAR_GEN3)
		dmr2 = VNDMR2_FTEV;
	else
		dmr2 = VNDMR2_FTEV | VNDMR2_VLV(1);

	if (!vin->is_csi) {
		/* Hsync Signal Polarity Select */
		if (!(vin->parallel->mbus_flags & V4L2_MBUS_HSYNC_ACTIVE_LOW))
			dmr2 |= VNDMR2_HPS;

		/* Vsync Signal Polarity Select */
		if (!(vin->parallel->mbus_flags & V4L2_MBUS_VSYNC_ACTIVE_LOW))
			dmr2 |= VNDMR2_VPS;

		/* Data Enable Polarity Select */
		if (vin->parallel->mbus_flags & V4L2_MBUS_DATA_ENABLE_LOW)
			dmr2 |= VNDMR2_CES;
	}

	/*
	 * Output format
	 */
	switch (vin->format.pixelformat) {
	case V4L2_PIX_FMT_NV16:
		rvin_write(vin,
			   ALIGN(vin->format.width * vin->format.height, 0x80),
			   VNUVAOF_REG);
		dmr = VNDMR_DTMD_YCSEP;
		output_is_yuv = true;
		break;
	case V4L2_PIX_FMT_YUYV:
		dmr = VNDMR_BPSM;
		output_is_yuv = true;
		break;
	case V4L2_PIX_FMT_UYVY:
		dmr = 0;
		output_is_yuv = true;
		break;
	case V4L2_PIX_FMT_XRGB555:
		dmr = VNDMR_DTMD_ARGB;
		break;
	case V4L2_PIX_FMT_RGB565:
		dmr = 0;
		break;
	case V4L2_PIX_FMT_XBGR32:
		/* Note: not supported on M1 */
		dmr = VNDMR_EXRGB;
		break;
	case V4L2_PIX_FMT_ARGB555:
		dmr = (vin->alpha ? VNDMR_ABIT : 0) | VNDMR_DTMD_ARGB;
		break;
	case V4L2_PIX_FMT_ABGR32:
		dmr = VNDMR_A8BIT(vin->alpha) | VNDMR_EXRGB | VNDMR_DTMD_ARGB;
		break;
	default:
		vin_err(vin, "Invalid pixelformat (0x%x)\n",
			vin->format.pixelformat);
		return -EINVAL;
	}

	/* Always update on field change */
	vnmc |= VNMC_VUP;

	/* If input and output use the same colorspace, use bypass mode */
	if (input_is_yuv == output_is_yuv)
		vnmc |= VNMC_BPS;

	if (vin->info->model == RCAR_GEN3) {
		/* Select between CSI-2 and parallel input */
		if (vin->is_csi)
			vnmc &= ~VNMC_DPINE;
		else
			vnmc |= VNMC_DPINE;
	}

	/* Progressive or interlaced mode */
	interrupts = progressive ? VNIE_FIE : VNIE_EFE;

	/* Ack interrupts */
	rvin_write(vin, interrupts, VNINTS_REG);
	/* Enable interrupts */
	rvin_write(vin, interrupts, VNIE_REG);
	/* Start capturing */
	rvin_write(vin, dmr, VNDMR_REG);
	rvin_write(vin, dmr2, VNDMR2_REG);

	/* Enable module */
	rvin_write(vin, vnmc | VNMC_ME, VNMC_REG);

	return 0;
}