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
struct fimc_fmt {unsigned int flags; scalar_t__ const fourcc; scalar_t__ const mbus_code; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (struct fimc_fmt*) ; 
 struct fimc_fmt* fimc_lite_formats ; 

__attribute__((used)) static const struct fimc_fmt *fimc_lite_find_format(const u32 *pixelformat,
			const u32 *mbus_code, unsigned int mask, int index)
{
	const struct fimc_fmt *fmt, *def_fmt = NULL;
	unsigned int i;
	int id = 0;

	if (index >= (int)ARRAY_SIZE(fimc_lite_formats))
		return NULL;

	for (i = 0; i < ARRAY_SIZE(fimc_lite_formats); ++i) {
		fmt = &fimc_lite_formats[i];
		if (mask && !(fmt->flags & mask))
			continue;
		if (pixelformat && fmt->fourcc == *pixelformat)
			return fmt;
		if (mbus_code && fmt->mbus_code == *mbus_code)
			return fmt;
		if (index == id)
			def_fmt = fmt;
		id++;
	}
	return def_fmt;
}