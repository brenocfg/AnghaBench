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
typedef  int u8 ;
typedef  int u32 ;
typedef  int u16 ;

/* Variables and functions */
 int OMAP_VRFB_LINE_LEN ; 
 int VRFB_PAGE_HEIGHT ; 

__attribute__((used)) static inline u32 get_extra_physical_size(u16 image_width_roundup, u8 bytespp)
{
	return (OMAP_VRFB_LINE_LEN - image_width_roundup) * VRFB_PAGE_HEIGHT *
		bytespp;
}