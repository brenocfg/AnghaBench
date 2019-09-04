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
struct pwc_device {int image_mask; } ;

/* Variables and functions */
 int PSZ_MAX ; 
 int** pwc_image_sizes ; 

int pwc_get_size(struct pwc_device *pdev, int width, int height)
{
	int i;

	/* Find the largest size supported by the camera that fits into the
	   requested size. */
	for (i = PSZ_MAX - 1; i >= 0; i--) {
		if (!(pdev->image_mask & (1 << i)))
			continue;

		if (pwc_image_sizes[i][0] <= width &&
		    pwc_image_sizes[i][1] <= height)
			return i;
	}

	/* No mode found, return the smallest mode we have */
	for (i = 0; i < PSZ_MAX; i++) {
		if (pdev->image_mask & (1 << i))
			return i;
	}

	/* Never reached there always is atleast one supported mode */
	return 0;
}