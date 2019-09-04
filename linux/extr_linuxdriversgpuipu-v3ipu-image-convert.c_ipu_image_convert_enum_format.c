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
typedef  int /*<<< orphan*/  u32 ;
struct ipu_image_pixfmt {int /*<<< orphan*/  fourcc; } ;

/* Variables and functions */
 scalar_t__ ARRAY_SIZE (struct ipu_image_pixfmt*) ; 
 int EINVAL ; 
 struct ipu_image_pixfmt* image_convert_formats ; 

int ipu_image_convert_enum_format(int index, u32 *fourcc)
{
	const struct ipu_image_pixfmt *fmt;

	if (index >= (int)ARRAY_SIZE(image_convert_formats))
		return -EINVAL;

	/* Format found */
	fmt = &image_convert_formats[index];
	*fourcc = fmt->fourcc;
	return 0;
}