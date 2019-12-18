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
typedef  unsigned int u32 ;

/* Variables and functions */
 int /*<<< orphan*/  v4l_bound_align_image (unsigned int*,unsigned int,unsigned int,unsigned int,unsigned int*,unsigned int,unsigned int,unsigned int,int) ; 

__attribute__((used)) static void jpu_bound_align_image(u32 *w, unsigned int w_min,
				  unsigned int w_max, unsigned int w_align,
				  u32 *h, unsigned int h_min,
				  unsigned int h_max, unsigned int h_align)
{
	unsigned int width, height, w_step, h_step;

	width = *w;
	height = *h;

	w_step = 1U << w_align;
	h_step = 1U << h_align;
	v4l_bound_align_image(w, w_min, w_max, w_align, h, h_min, h_max,
			      h_align, 3);

	if (*w < width && *w + w_step < w_max)
		*w += w_step;
	if (*h < height && *h + h_step < h_max)
		*h += h_step;
}