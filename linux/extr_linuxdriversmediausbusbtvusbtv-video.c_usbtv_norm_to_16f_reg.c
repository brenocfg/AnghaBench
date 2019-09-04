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
typedef  int v4l2_std_id ;
typedef  int uint16_t ;

/* Variables and functions */
 int V4L2_STD_NTSC ; 
 int V4L2_STD_NTSC_443 ; 
 int V4L2_STD_PAL ; 
 int V4L2_STD_PAL_60 ; 
 int V4L2_STD_PAL_M ; 
 int V4L2_STD_SECAM ; 

__attribute__((used)) static uint16_t usbtv_norm_to_16f_reg(v4l2_std_id norm)
{
	/* NTSC M/M-JP/M-KR */
	if (norm & V4L2_STD_NTSC)
		return 0x00b8;
	/* PAL BG/DK/H/I */
	if (norm & V4L2_STD_PAL)
		return 0x00ee;
	/* SECAM B/D/G/H/K/K1/L/Lc */
	if (norm & V4L2_STD_SECAM)
		return 0x00ff;
	if (norm & V4L2_STD_NTSC_443)
		return 0x00a8;
	if (norm & (V4L2_STD_PAL_M | V4L2_STD_PAL_60))
		return 0x00bc;
	/* Fallback to automatic detection for other standards */
	return 0x0000;
}