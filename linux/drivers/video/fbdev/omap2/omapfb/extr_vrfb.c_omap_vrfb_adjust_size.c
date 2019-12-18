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
typedef  int u16 ;

/* Variables and functions */
 int ALIGN (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VRFB_PAGE_HEIGHT ; 
 int /*<<< orphan*/  VRFB_PAGE_WIDTH ; 

void omap_vrfb_adjust_size(u16 *width, u16 *height,
		u8 bytespp)
{
	*width = ALIGN(*width * bytespp, VRFB_PAGE_WIDTH) / bytespp;
	*height = ALIGN(*height, VRFB_PAGE_HEIGHT);
}