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
struct TYPE_2__ {int pixelformat; unsigned int width; } ;
struct sh_vou_device {TYPE_1__ pix; } ;

/* Variables and functions */
#define  V4L2_PIX_FMT_NV12 132 
#define  V4L2_PIX_FMT_NV16 131 
#define  V4L2_PIX_FMT_RGB24 130 
#define  V4L2_PIX_FMT_RGB565 129 
#define  V4L2_PIX_FMT_RGB565X 128 
 int /*<<< orphan*/  VOUAIR ; 
 int /*<<< orphan*/  VOUSWR ; 
 int /*<<< orphan*/  sh_vou_reg_a_write (struct sh_vou_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sh_vou_reg_ab_write (struct sh_vou_device*,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static void sh_vou_stream_config(struct sh_vou_device *vou_dev)
{
	unsigned int row_coeff;
#ifdef __LITTLE_ENDIAN
	u32 dataswap = 7;
#else
	u32 dataswap = 0;
#endif

	switch (vou_dev->pix.pixelformat) {
	default:
	case V4L2_PIX_FMT_NV12:
	case V4L2_PIX_FMT_NV16:
		row_coeff = 1;
		break;
	case V4L2_PIX_FMT_RGB565:
		dataswap ^= 1;
		/* fall through */
	case V4L2_PIX_FMT_RGB565X:
		row_coeff = 2;
		break;
	case V4L2_PIX_FMT_RGB24:
		row_coeff = 3;
		break;
	}

	sh_vou_reg_a_write(vou_dev, VOUSWR, dataswap);
	sh_vou_reg_ab_write(vou_dev, VOUAIR, vou_dev->pix.width * row_coeff);
}