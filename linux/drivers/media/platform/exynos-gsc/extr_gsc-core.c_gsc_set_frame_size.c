#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int width; int height; scalar_t__ top; scalar_t__ left; } ;
struct gsc_frame {int f_width; int f_height; TYPE_1__ crop; } ;

/* Variables and functions */

void gsc_set_frame_size(struct gsc_frame *frame, int width, int height)
{
	frame->f_width	= width;
	frame->f_height	= height;
	frame->crop.width = width;
	frame->crop.height = height;
	frame->crop.left = 0;
	frame->crop.top = 0;
}