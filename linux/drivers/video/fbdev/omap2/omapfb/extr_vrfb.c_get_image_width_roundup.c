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
typedef  unsigned long u8 ;
typedef  unsigned long u32 ;
typedef  unsigned long u16 ;

/* Variables and functions */
 unsigned long VRFB_PAGE_WIDTH ; 

__attribute__((used)) static u32 get_image_width_roundup(u16 width, u8 bytespp)
{
	unsigned long stride = width * bytespp;
	unsigned long ceil_pages_per_stride = (stride / VRFB_PAGE_WIDTH) +
		(stride % VRFB_PAGE_WIDTH != 0);

	return ceil_pages_per_stride * VRFB_PAGE_WIDTH / bytespp;
}