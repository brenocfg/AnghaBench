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
typedef  int s8 ;

/* Variables and functions */
#define  V4L2_PIX_FMT_H264 128 

__attribute__((used)) static s8 v4l2_pixelformat_to_mcu_codec(u32 pixelformat)
{
	switch (pixelformat) {
	case V4L2_PIX_FMT_H264:
	default:
		return 1;
	}
}