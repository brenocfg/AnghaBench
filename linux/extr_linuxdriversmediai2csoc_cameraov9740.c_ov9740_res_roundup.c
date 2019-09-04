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
 scalar_t__ ALIGN (scalar_t__,int) ; 
 scalar_t__ OV9740_MAX_HEIGHT ; 
 scalar_t__ OV9740_MAX_WIDTH ; 

__attribute__((used)) static void ov9740_res_roundup(u32 *width, u32 *height)
{
	/* Width must be a multiple of 4 pixels. */
	*width = ALIGN(*width, 4);

	/* Max resolution is 1280x720 (720p). */
	if (*width > OV9740_MAX_WIDTH)
		*width = OV9740_MAX_WIDTH;

	if (*height > OV9740_MAX_HEIGHT)
		*height = OV9740_MAX_HEIGHT;
}