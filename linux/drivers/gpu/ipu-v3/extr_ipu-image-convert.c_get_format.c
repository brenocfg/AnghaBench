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
struct ipu_image_pixfmt {scalar_t__ fourcc; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (struct ipu_image_pixfmt*) ; 
 struct ipu_image_pixfmt* image_convert_formats ; 

__attribute__((used)) static const struct ipu_image_pixfmt *get_format(u32 fourcc)
{
	const struct ipu_image_pixfmt *ret = NULL;
	unsigned int i;

	for (i = 0; i < ARRAY_SIZE(image_convert_formats); i++) {
		if (image_convert_formats[i].fourcc == fourcc) {
			ret = &image_convert_formats[i];
			break;
		}
	}

	return ret;
}