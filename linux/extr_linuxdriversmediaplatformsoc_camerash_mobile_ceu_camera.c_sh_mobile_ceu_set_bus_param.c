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
typedef  int /*<<< orphan*/  u32 ;
struct v4l2_subdev {int dummy; } ;
struct v4l2_mbus_config {unsigned long flags; int /*<<< orphan*/  type; } ;
struct soc_camera_host {struct sh_mobile_ceu_dev* priv; } ;
struct soc_camera_device {int /*<<< orphan*/  parent; TYPE_2__* current_fmt; struct sh_mobile_ceu_cam* host_priv; } ;
struct sh_mobile_ceu_dev {int flags; int is_16bit; int field; unsigned long cflcr; } ;
struct sh_mobile_ceu_cam {int /*<<< orphan*/  code; } ;
struct TYPE_4__ {TYPE_1__* host_fmt; } ;
struct TYPE_3__ {int bits_per_sample; int fourcc; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  CAIFR ; 
 int /*<<< orphan*/  CAMCR ; 
 int /*<<< orphan*/  CAPCR ; 
 int /*<<< orphan*/  CDOCR ; 
 unsigned long CEU_BUS_FLAGS ; 
 int /*<<< orphan*/  CFLCR ; 
 int /*<<< orphan*/  CFWCR ; 
 int /*<<< orphan*/  CRCMPR ; 
 int /*<<< orphan*/  CRCNTR ; 
 int EINVAL ; 
 int ENOIOCTLCMD ; 
#define  MEDIA_BUS_FMT_UYVY8_2X8 137 
#define  MEDIA_BUS_FMT_VYUY8_2X8 136 
#define  MEDIA_BUS_FMT_YUYV8_2X8 135 
#define  MEDIA_BUS_FMT_YVYU8_2X8 134 
 int SH_CEU_FLAG_HSYNC_LOW ; 
 int SH_CEU_FLAG_LOWER_8BIT ; 
 int SH_CEU_FLAG_VSYNC_LOW ; 
#define  V4L2_FIELD_INTERLACED_BT 133 
#define  V4L2_FIELD_INTERLACED_TB 132 
 unsigned long V4L2_MBUS_HSYNC_ACTIVE_HIGH ; 
 unsigned long V4L2_MBUS_HSYNC_ACTIVE_LOW ; 
 int /*<<< orphan*/  V4L2_MBUS_PARALLEL ; 
 unsigned long V4L2_MBUS_VSYNC_ACTIVE_HIGH ; 
 unsigned long V4L2_MBUS_VSYNC_ACTIVE_LOW ; 
#define  V4L2_PIX_FMT_NV12 131 
#define  V4L2_PIX_FMT_NV16 130 
#define  V4L2_PIX_FMT_NV21 129 
#define  V4L2_PIX_FMT_NV61 128 
 int /*<<< orphan*/  capture_restore (struct sh_mobile_ceu_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  capture_save_reset (struct sh_mobile_ceu_dev*) ; 
 int /*<<< orphan*/  ceu_write (struct sh_mobile_ceu_dev*,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  dev_geo (int /*<<< orphan*/ ,char*,unsigned long) ; 
 int /*<<< orphan*/  g_mbus_config ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  s_mbus_config ; 
 int /*<<< orphan*/  sh_mobile_ceu_set_rect (struct soc_camera_device*) ; 
 struct v4l2_subdev* soc_camera_to_subdev (struct soc_camera_device*) ; 
 unsigned long soc_mbus_config_compatible (struct v4l2_mbus_config*,unsigned long) ; 
 struct soc_camera_host* to_soc_camera_host (int /*<<< orphan*/ ) ; 
 int v4l2_subdev_call (struct v4l2_subdev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct v4l2_mbus_config*) ; 
 int /*<<< orphan*/  video ; 

__attribute__((used)) static int sh_mobile_ceu_set_bus_param(struct soc_camera_device *icd)
{
	struct soc_camera_host *ici = to_soc_camera_host(icd->parent);
	struct sh_mobile_ceu_dev *pcdev = ici->priv;
	struct v4l2_subdev *sd = soc_camera_to_subdev(icd);
	struct sh_mobile_ceu_cam *cam = icd->host_priv;
	struct v4l2_mbus_config cfg = {.type = V4L2_MBUS_PARALLEL,};
	unsigned long value, common_flags = CEU_BUS_FLAGS;
	u32 capsr = capture_save_reset(pcdev);
	unsigned int yuv_lineskip;
	int ret;

	/*
	 * If the client doesn't implement g_mbus_config, we just use our
	 * platform data
	 */
	ret = v4l2_subdev_call(sd, video, g_mbus_config, &cfg);
	if (!ret) {
		common_flags = soc_mbus_config_compatible(&cfg,
							  common_flags);
		if (!common_flags)
			return -EINVAL;
	} else if (ret != -ENOIOCTLCMD) {
		return ret;
	}

	/* Make choises, based on platform preferences */
	if ((common_flags & V4L2_MBUS_HSYNC_ACTIVE_HIGH) &&
	    (common_flags & V4L2_MBUS_HSYNC_ACTIVE_LOW)) {
		if (pcdev->flags & SH_CEU_FLAG_HSYNC_LOW)
			common_flags &= ~V4L2_MBUS_HSYNC_ACTIVE_HIGH;
		else
			common_flags &= ~V4L2_MBUS_HSYNC_ACTIVE_LOW;
	}

	if ((common_flags & V4L2_MBUS_VSYNC_ACTIVE_HIGH) &&
	    (common_flags & V4L2_MBUS_VSYNC_ACTIVE_LOW)) {
		if (pcdev->flags & SH_CEU_FLAG_VSYNC_LOW)
			common_flags &= ~V4L2_MBUS_VSYNC_ACTIVE_HIGH;
		else
			common_flags &= ~V4L2_MBUS_VSYNC_ACTIVE_LOW;
	}

	cfg.flags = common_flags;
	ret = v4l2_subdev_call(sd, video, s_mbus_config, &cfg);
	if (ret < 0 && ret != -ENOIOCTLCMD)
		return ret;

	if (icd->current_fmt->host_fmt->bits_per_sample > 8)
		pcdev->is_16bit = 1;
	else
		pcdev->is_16bit = 0;

	ceu_write(pcdev, CRCNTR, 0);
	ceu_write(pcdev, CRCMPR, 0);

	value = 0x00000010; /* data fetch by default */
	yuv_lineskip = 0x10;

	switch (icd->current_fmt->host_fmt->fourcc) {
	case V4L2_PIX_FMT_NV12:
	case V4L2_PIX_FMT_NV21:
		/* convert 4:2:2 -> 4:2:0 */
		yuv_lineskip = 0; /* skip for NV12/21, no skip for NV16/61 */
		/* fall-through */
	case V4L2_PIX_FMT_NV16:
	case V4L2_PIX_FMT_NV61:
		switch (cam->code) {
		case MEDIA_BUS_FMT_UYVY8_2X8:
			value = 0x00000000; /* Cb0, Y0, Cr0, Y1 */
			break;
		case MEDIA_BUS_FMT_VYUY8_2X8:
			value = 0x00000100; /* Cr0, Y0, Cb0, Y1 */
			break;
		case MEDIA_BUS_FMT_YUYV8_2X8:
			value = 0x00000200; /* Y0, Cb0, Y1, Cr0 */
			break;
		case MEDIA_BUS_FMT_YVYU8_2X8:
			value = 0x00000300; /* Y0, Cr0, Y1, Cb0 */
			break;
		default:
			BUG();
		}
	}

	if (icd->current_fmt->host_fmt->fourcc == V4L2_PIX_FMT_NV21 ||
	    icd->current_fmt->host_fmt->fourcc == V4L2_PIX_FMT_NV61)
		value ^= 0x00000100; /* swap U, V to change from NV1x->NVx1 */

	value |= common_flags & V4L2_MBUS_VSYNC_ACTIVE_LOW ? 1 << 1 : 0;
	value |= common_flags & V4L2_MBUS_HSYNC_ACTIVE_LOW ? 1 << 0 : 0;

	if (pcdev->is_16bit)
		value |= 1 << 12;
	else if (pcdev->flags & SH_CEU_FLAG_LOWER_8BIT)
		value |= 2 << 12;

	ceu_write(pcdev, CAMCR, value);

	ceu_write(pcdev, CAPCR, 0x00300000);

	switch (pcdev->field) {
	case V4L2_FIELD_INTERLACED_TB:
		value = 0x101;
		break;
	case V4L2_FIELD_INTERLACED_BT:
		value = 0x102;
		break;
	default:
		value = 0;
		break;
	}
	ceu_write(pcdev, CAIFR, value);

	sh_mobile_ceu_set_rect(icd);
	mdelay(1);

	dev_geo(icd->parent, "CFLCR 0x%x\n", pcdev->cflcr);
	ceu_write(pcdev, CFLCR, pcdev->cflcr);

	/*
	 * A few words about byte order (observed in Big Endian mode)
	 *
	 * In data fetch mode bytes are received in chunks of 8 bytes.
	 * D0, D1, D2, D3, D4, D5, D6, D7 (D0 received first)
	 *
	 * The data is however by default written to memory in reverse order:
	 * D7, D6, D5, D4, D3, D2, D1, D0 (D7 written to lowest byte)
	 *
	 * The lowest three bits of CDOCR allows us to do swapping,
	 * using 7 we swap the data bytes to match the incoming order:
	 * D0, D1, D2, D3, D4, D5, D6, D7
	 */
	value = 0x00000007 | yuv_lineskip;

	ceu_write(pcdev, CDOCR, value);
	ceu_write(pcdev, CFWCR, 0); /* keep "datafetch firewall" disabled */

	capture_restore(pcdev, capsr);

	/* not in bundle mode: skip CBDSR, CDAYR2, CDACR2, CDBYR2, CDBCR2 */
	return 0;
}