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
typedef  scalar_t__ u32 ;

/* Variables and functions */
 int EINVAL ; 
 int SOLO_DEV_6010 ; 
 int SOLO_DEV_6110 ; 
 scalar_t__ V4L2_PIX_FMT_H264 ; 
 scalar_t__ V4L2_PIX_FMT_MJPEG ; 
 scalar_t__ V4L2_PIX_FMT_MPEG4 ; 

__attribute__((used)) static inline int solo_valid_pixfmt(u32 pixfmt, int dev_type)
{
	return (pixfmt == V4L2_PIX_FMT_H264 && dev_type == SOLO_DEV_6110)
		|| (pixfmt == V4L2_PIX_FMT_MPEG4 && dev_type == SOLO_DEV_6010)
		|| pixfmt == V4L2_PIX_FMT_MJPEG ? 0 : -EINVAL;
}