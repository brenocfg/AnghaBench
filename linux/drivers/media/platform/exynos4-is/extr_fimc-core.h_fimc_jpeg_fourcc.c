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
 scalar_t__ V4L2_PIX_FMT_JPEG ; 
 scalar_t__ V4L2_PIX_FMT_S5C_UYVY_JPG ; 

__attribute__((used)) static inline bool fimc_jpeg_fourcc(u32 pixelformat)
{
	return (pixelformat == V4L2_PIX_FMT_JPEG ||
		pixelformat == V4L2_PIX_FMT_S5C_UYVY_JPG);
}