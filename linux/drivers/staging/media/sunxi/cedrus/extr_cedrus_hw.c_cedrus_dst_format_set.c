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
typedef  int u32 ;
struct v4l2_pix_format {unsigned int width; unsigned int height; int pixelformat; } ;
struct cedrus_dev {int dummy; } ;

/* Variables and functions */
 int ALIGN (unsigned int,int) ; 
#define  V4L2_PIX_FMT_NV12 129 
#define  V4L2_PIX_FMT_SUNXI_TILED_NV12 128 
 int /*<<< orphan*/  VE_CHROMA_BUF_LEN ; 
 int /*<<< orphan*/  VE_PRIMARY_CHROMA_BUF_LEN ; 
 int /*<<< orphan*/  VE_PRIMARY_FB_LINE_STRIDE ; 
 int VE_PRIMARY_FB_LINE_STRIDE_CHROMA (int) ; 
 int VE_PRIMARY_FB_LINE_STRIDE_LUMA (int) ; 
 int /*<<< orphan*/  VE_PRIMARY_OUT_FMT ; 
 int VE_PRIMARY_OUT_FMT_NV12 ; 
 int VE_PRIMARY_OUT_FMT_TILED_32_NV12 ; 
 int VE_SECONDARY_OUT_FMT_TILED_32_NV12 ; 
 int /*<<< orphan*/  cedrus_write (struct cedrus_dev*,int /*<<< orphan*/ ,int) ; 

void cedrus_dst_format_set(struct cedrus_dev *dev,
			   struct v4l2_pix_format *fmt)
{
	unsigned int width = fmt->width;
	unsigned int height = fmt->height;
	u32 chroma_size;
	u32 reg;

	switch (fmt->pixelformat) {
	case V4L2_PIX_FMT_NV12:
		chroma_size = ALIGN(width, 16) * ALIGN(height, 16) / 2;

		reg = VE_PRIMARY_OUT_FMT_NV12;
		cedrus_write(dev, VE_PRIMARY_OUT_FMT, reg);

		reg = chroma_size / 2;
		cedrus_write(dev, VE_PRIMARY_CHROMA_BUF_LEN, reg);

		reg = VE_PRIMARY_FB_LINE_STRIDE_LUMA(ALIGN(width, 16)) |
		      VE_PRIMARY_FB_LINE_STRIDE_CHROMA(ALIGN(width, 16) / 2);
		cedrus_write(dev, VE_PRIMARY_FB_LINE_STRIDE, reg);

		break;
	case V4L2_PIX_FMT_SUNXI_TILED_NV12:
	default:
		reg = VE_PRIMARY_OUT_FMT_TILED_32_NV12;
		cedrus_write(dev, VE_PRIMARY_OUT_FMT, reg);

		reg = VE_SECONDARY_OUT_FMT_TILED_32_NV12;
		cedrus_write(dev, VE_CHROMA_BUF_LEN, reg);

		break;
	}
}