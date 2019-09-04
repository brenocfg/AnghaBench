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
struct tpg_data {int fourcc; } ;

/* Variables and functions */
#define  V4L2_PIX_FMT_SBGGR10 139 
#define  V4L2_PIX_FMT_SBGGR12 138 
#define  V4L2_PIX_FMT_SBGGR8 137 
#define  V4L2_PIX_FMT_SGBRG10 136 
#define  V4L2_PIX_FMT_SGBRG12 135 
#define  V4L2_PIX_FMT_SGBRG8 134 
#define  V4L2_PIX_FMT_SGRBG10 133 
#define  V4L2_PIX_FMT_SGRBG12 132 
#define  V4L2_PIX_FMT_SGRBG8 131 
#define  V4L2_PIX_FMT_SRGGB10 130 
#define  V4L2_PIX_FMT_SRGGB12 129 
#define  V4L2_PIX_FMT_SRGGB8 128 

unsigned tpg_g_interleaved_plane(const struct tpg_data *tpg, unsigned buf_line)
{
	switch (tpg->fourcc) {
	case V4L2_PIX_FMT_SBGGR8:
	case V4L2_PIX_FMT_SGBRG8:
	case V4L2_PIX_FMT_SGRBG8:
	case V4L2_PIX_FMT_SRGGB8:
	case V4L2_PIX_FMT_SBGGR10:
	case V4L2_PIX_FMT_SGBRG10:
	case V4L2_PIX_FMT_SGRBG10:
	case V4L2_PIX_FMT_SRGGB10:
	case V4L2_PIX_FMT_SBGGR12:
	case V4L2_PIX_FMT_SGBRG12:
	case V4L2_PIX_FMT_SGRBG12:
	case V4L2_PIX_FMT_SRGGB12:
		return buf_line & 1;
	default:
		return 0;
	}
}