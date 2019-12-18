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
struct pxp_fmt {int fourcc; int depth; } ;

/* Variables and functions */
#define  V4L2_PIX_FMT_NV12 133 
#define  V4L2_PIX_FMT_NV16 132 
#define  V4L2_PIX_FMT_NV21 131 
#define  V4L2_PIX_FMT_NV61 130 
#define  V4L2_PIX_FMT_YUV420 129 
#define  V4L2_PIX_FMT_YUV422P 128 

__attribute__((used)) static inline u32 pxp_bytesperline(struct pxp_fmt *fmt, u32 width)
{
	switch (fmt->fourcc) {
	case V4L2_PIX_FMT_YUV420:
	case V4L2_PIX_FMT_NV12:
	case V4L2_PIX_FMT_NV21:
	case V4L2_PIX_FMT_YUV422P:
	case V4L2_PIX_FMT_NV16:
	case V4L2_PIX_FMT_NV61:
		return width;
	default:
		return (width * fmt->depth) >> 3;
	}
}