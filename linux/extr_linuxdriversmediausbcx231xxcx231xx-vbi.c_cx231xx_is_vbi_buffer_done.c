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
typedef  scalar_t__ u32 ;
struct cx231xx_dmaqueue {scalar_t__ lines_completed; int current_field; } ;
struct cx231xx {int norm; } ;

/* Variables and functions */
 scalar_t__ NTSC_VBI_LINES ; 
 scalar_t__ PAL_VBI_LINES ; 
 int V4L2_STD_625_50 ; 

u8 cx231xx_is_vbi_buffer_done(struct cx231xx *dev,
			      struct cx231xx_dmaqueue *dma_q)
{
	u32 height = 0;

	height = ((dev->norm & V4L2_STD_625_50) ?
		  PAL_VBI_LINES : NTSC_VBI_LINES);
	if (dma_q->lines_completed == height && dma_q->current_field == 2)
		return 1;
	else
		return 0;
}