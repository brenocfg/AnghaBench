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

/* Variables and functions */
 int EINVAL ; 
#define  V4L2_PIX_FMT_NV12 128 

__attribute__((used)) static u32 v4l2_pixelformat_to_mcu_format(u32 pixelformat)
{
	switch (pixelformat) {
	case V4L2_PIX_FMT_NV12:
		/* AL_420_8BITS: 0x100 -> NV12, 0x88 -> 8 bit */
		return 0x100 | 0x88;
	default:
		return -EINVAL;
	}
}