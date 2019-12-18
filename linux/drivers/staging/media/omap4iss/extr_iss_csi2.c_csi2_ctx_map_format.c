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
typedef  int /*<<< orphan*/  u16 ;
struct v4l2_mbus_framefmt {int code; } ;
struct iss_csi2_device {int output; size_t dpcm_decompress; scalar_t__ frame_skip; struct v4l2_mbus_framefmt* formats; } ;

/* Variables and functions */
 int CSI2_OUTPUT_IPIPEIF ; 
 int CSI2_OUTPUT_MEMORY ; 
 size_t CSI2_PAD_SINK ; 
 int /*<<< orphan*/  CSI2_PIX_FMT_OTHERS ; 
#define  MEDIA_BUS_FMT_SBGGR10_1X10 141 
#define  MEDIA_BUS_FMT_SBGGR10_DPCM8_1X8 140 
#define  MEDIA_BUS_FMT_SBGGR8_1X8 139 
#define  MEDIA_BUS_FMT_SGBRG10_1X10 138 
#define  MEDIA_BUS_FMT_SGBRG10_DPCM8_1X8 137 
#define  MEDIA_BUS_FMT_SGBRG8_1X8 136 
#define  MEDIA_BUS_FMT_SGRBG10_1X10 135 
#define  MEDIA_BUS_FMT_SGRBG10_DPCM8_1X8 134 
#define  MEDIA_BUS_FMT_SGRBG8_1X8 133 
#define  MEDIA_BUS_FMT_SRGGB10_1X10 132 
#define  MEDIA_BUS_FMT_SRGGB10_DPCM8_1X8 131 
#define  MEDIA_BUS_FMT_SRGGB8_1X8 130 
#define  MEDIA_BUS_FMT_UYVY8_1X16 129 
#define  MEDIA_BUS_FMT_YUYV8_1X16 128 
 int /*<<< orphan*/  WARN (int,char*,int) ; 
 int /*<<< orphan*/ *** __csi2_fmt_map ; 

__attribute__((used)) static u16 csi2_ctx_map_format(struct iss_csi2_device *csi2)
{
	const struct v4l2_mbus_framefmt *fmt = &csi2->formats[CSI2_PAD_SINK];
	int fmtidx, destidx;

	switch (fmt->code) {
	case MEDIA_BUS_FMT_SGRBG10_1X10:
	case MEDIA_BUS_FMT_SRGGB10_1X10:
	case MEDIA_BUS_FMT_SBGGR10_1X10:
	case MEDIA_BUS_FMT_SGBRG10_1X10:
		fmtidx = 0;
		break;
	case MEDIA_BUS_FMT_SGRBG10_DPCM8_1X8:
	case MEDIA_BUS_FMT_SRGGB10_DPCM8_1X8:
	case MEDIA_BUS_FMT_SBGGR10_DPCM8_1X8:
	case MEDIA_BUS_FMT_SGBRG10_DPCM8_1X8:
		fmtidx = 1;
		break;
	case MEDIA_BUS_FMT_SBGGR8_1X8:
	case MEDIA_BUS_FMT_SGBRG8_1X8:
	case MEDIA_BUS_FMT_SGRBG8_1X8:
	case MEDIA_BUS_FMT_SRGGB8_1X8:
		fmtidx = 2;
		break;
	case MEDIA_BUS_FMT_UYVY8_1X16:
	case MEDIA_BUS_FMT_YUYV8_1X16:
		fmtidx = 3;
		break;
	default:
		WARN(1, "CSI2: pixel format %08x unsupported!\n",
		     fmt->code);
		return 0;
	}

	if (!(csi2->output & CSI2_OUTPUT_IPIPEIF) &&
	    !(csi2->output & CSI2_OUTPUT_MEMORY)) {
		/* Neither output enabled is a valid combination */
		return CSI2_PIX_FMT_OTHERS;
	}

	/* If we need to skip frames at the beginning of the stream disable the
	 * video port to avoid sending the skipped frames to the IPIPEIF.
	 */
	destidx = csi2->frame_skip ? 0 : !!(csi2->output & CSI2_OUTPUT_IPIPEIF);

	return __csi2_fmt_map[fmtidx][destidx][csi2->dpcm_decompress];
}