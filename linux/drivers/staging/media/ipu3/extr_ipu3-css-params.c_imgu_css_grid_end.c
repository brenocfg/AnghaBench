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
 int IPU3_UAPI_GRID_START_MASK ; 

__attribute__((used)) static u16 imgu_css_grid_end(u16 start, u8 width, u8 block_width_log2)
{
	return (start & IPU3_UAPI_GRID_START_MASK) +
		(width << block_width_log2) - 1;
}