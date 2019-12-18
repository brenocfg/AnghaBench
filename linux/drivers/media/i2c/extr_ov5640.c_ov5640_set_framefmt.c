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
typedef  int u8 ;
struct v4l2_mbus_framefmt {int code; } ;
struct ov5640_dev {int dummy; } ;

/* Variables and functions */
 int BIT (int) ; 
 int EINVAL ; 
#define  MEDIA_BUS_FMT_JPEG_1X8 136 
#define  MEDIA_BUS_FMT_RGB565_2X8_BE 135 
#define  MEDIA_BUS_FMT_RGB565_2X8_LE 134 
#define  MEDIA_BUS_FMT_SBGGR8_1X8 133 
#define  MEDIA_BUS_FMT_SGBRG8_1X8 132 
#define  MEDIA_BUS_FMT_SGRBG8_1X8 131 
#define  MEDIA_BUS_FMT_SRGGB8_1X8 130 
#define  MEDIA_BUS_FMT_UYVY8_2X8 129 
#define  MEDIA_BUS_FMT_YUYV8_2X8 128 
 int OV5640_FMT_MUX_RAW_DPC ; 
 int OV5640_FMT_MUX_RGB ; 
 int OV5640_FMT_MUX_YUV422 ; 
 int /*<<< orphan*/  OV5640_REG_FORMAT_CONTROL00 ; 
 int /*<<< orphan*/  OV5640_REG_ISP_FORMAT_MUX_CTRL ; 
 int /*<<< orphan*/  OV5640_REG_SYS_CLOCK_ENABLE02 ; 
 int /*<<< orphan*/  OV5640_REG_SYS_RESET02 ; 
 int /*<<< orphan*/  OV5640_REG_TIMING_TC_REG21 ; 
 int ov5640_mod_reg (struct ov5640_dev*,int /*<<< orphan*/ ,int,int) ; 
 int ov5640_write_reg (struct ov5640_dev*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ov5640_set_framefmt(struct ov5640_dev *sensor,
			       struct v4l2_mbus_framefmt *format)
{
	int ret = 0;
	bool is_jpeg = false;
	u8 fmt, mux;

	switch (format->code) {
	case MEDIA_BUS_FMT_UYVY8_2X8:
		/* YUV422, UYVY */
		fmt = 0x3f;
		mux = OV5640_FMT_MUX_YUV422;
		break;
	case MEDIA_BUS_FMT_YUYV8_2X8:
		/* YUV422, YUYV */
		fmt = 0x30;
		mux = OV5640_FMT_MUX_YUV422;
		break;
	case MEDIA_BUS_FMT_RGB565_2X8_LE:
		/* RGB565 {g[2:0],b[4:0]},{r[4:0],g[5:3]} */
		fmt = 0x6F;
		mux = OV5640_FMT_MUX_RGB;
		break;
	case MEDIA_BUS_FMT_RGB565_2X8_BE:
		/* RGB565 {r[4:0],g[5:3]},{g[2:0],b[4:0]} */
		fmt = 0x61;
		mux = OV5640_FMT_MUX_RGB;
		break;
	case MEDIA_BUS_FMT_JPEG_1X8:
		/* YUV422, YUYV */
		fmt = 0x30;
		mux = OV5640_FMT_MUX_YUV422;
		is_jpeg = true;
		break;
	case MEDIA_BUS_FMT_SBGGR8_1X8:
		/* Raw, BGBG... / GRGR... */
		fmt = 0x00;
		mux = OV5640_FMT_MUX_RAW_DPC;
		break;
	case MEDIA_BUS_FMT_SGBRG8_1X8:
		/* Raw bayer, GBGB... / RGRG... */
		fmt = 0x01;
		mux = OV5640_FMT_MUX_RAW_DPC;
		break;
	case MEDIA_BUS_FMT_SGRBG8_1X8:
		/* Raw bayer, GRGR... / BGBG... */
		fmt = 0x02;
		mux = OV5640_FMT_MUX_RAW_DPC;
		break;
	case MEDIA_BUS_FMT_SRGGB8_1X8:
		/* Raw bayer, RGRG... / GBGB... */
		fmt = 0x03;
		mux = OV5640_FMT_MUX_RAW_DPC;
		break;
	default:
		return -EINVAL;
	}

	/* FORMAT CONTROL00: YUV and RGB formatting */
	ret = ov5640_write_reg(sensor, OV5640_REG_FORMAT_CONTROL00, fmt);
	if (ret)
		return ret;

	/* FORMAT MUX CONTROL: ISP YUV or RGB */
	ret = ov5640_write_reg(sensor, OV5640_REG_ISP_FORMAT_MUX_CTRL, mux);
	if (ret)
		return ret;

	/*
	 * TIMING TC REG21:
	 * - [5]:	JPEG enable
	 */
	ret = ov5640_mod_reg(sensor, OV5640_REG_TIMING_TC_REG21,
			     BIT(5), is_jpeg ? BIT(5) : 0);
	if (ret)
		return ret;

	/*
	 * SYSTEM RESET02:
	 * - [4]:	Reset JFIFO
	 * - [3]:	Reset SFIFO
	 * - [2]:	Reset JPEG
	 */
	ret = ov5640_mod_reg(sensor, OV5640_REG_SYS_RESET02,
			     BIT(4) | BIT(3) | BIT(2),
			     is_jpeg ? 0 : (BIT(4) | BIT(3) | BIT(2)));
	if (ret)
		return ret;

	/*
	 * CLOCK ENABLE02:
	 * - [5]:	Enable JPEG 2x clock
	 * - [3]:	Enable JPEG clock
	 */
	return ov5640_mod_reg(sensor, OV5640_REG_SYS_CLOCK_ENABLE02,
			      BIT(5) | BIT(3),
			      is_jpeg ? (BIT(5) | BIT(3)) : 0);
}