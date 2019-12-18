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
struct em28xx {int dummy; } ;

/* Variables and functions */
 unsigned int norm_maxh (struct em28xx*) ; 
 unsigned int norm_maxw (struct em28xx*) ; 

__attribute__((used)) static void scale_to_size(struct em28xx *dev,
			  unsigned int hscale, unsigned int vscale,
			  unsigned int *width, unsigned int *height)
{
	unsigned int          maxw = norm_maxw(dev);
	unsigned int          maxh = norm_maxh(dev);

	*width = (((unsigned long)maxw) << 12) / (hscale + 4096L);
	*height = (((unsigned long)maxh) << 12) / (vscale + 4096L);

	/* Don't let width or height to be zero */
	if (*width < 1)
		*width = 1;
	if (*height < 1)
		*height = 1;
}