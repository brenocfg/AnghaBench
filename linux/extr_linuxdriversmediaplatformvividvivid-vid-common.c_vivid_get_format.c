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
struct vivid_fmt {scalar_t__ fourcc; int buffers; } ;
struct vivid_dev {scalar_t__ multiplanar; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (struct vivid_fmt*) ; 
 struct vivid_fmt* vivid_formats ; 

const struct vivid_fmt *vivid_get_format(struct vivid_dev *dev, u32 pixelformat)
{
	const struct vivid_fmt *fmt;
	unsigned k;

	for (k = 0; k < ARRAY_SIZE(vivid_formats); k++) {
		fmt = &vivid_formats[k];
		if (fmt->fourcc == pixelformat)
			if (fmt->buffers == 1 || dev->multiplanar)
				return fmt;
	}

	return NULL;
}