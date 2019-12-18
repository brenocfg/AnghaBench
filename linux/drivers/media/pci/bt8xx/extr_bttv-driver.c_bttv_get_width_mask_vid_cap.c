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
struct bttv_format {int flags; } ;

/* Variables and functions */
 int FORMAT_FLAGS_PLANAR ; 

__attribute__((used)) static void bttv_get_width_mask_vid_cap(const struct bttv_format *fmt,
					unsigned int *width_mask,
					unsigned int *width_bias)
{
	if (fmt->flags & FORMAT_FLAGS_PLANAR) {
		*width_mask = ~15; /* width must be a multiple of 16 pixels */
		*width_bias = 8;   /* nearest */
	} else {
		*width_mask = ~3; /* width must be a multiple of 4 pixels */
		*width_bias = 2;  /* nearest */
	}
}