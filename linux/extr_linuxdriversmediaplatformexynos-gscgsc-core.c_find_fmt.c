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
struct gsc_fmt {scalar_t__ pixelformat; scalar_t__ mbus_code; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 struct gsc_fmt* get_format (unsigned int) ; 
 int /*<<< orphan*/  gsc_formats ; 

const struct gsc_fmt *find_fmt(u32 *pixelformat, u32 *mbus_code, u32 index)
{
	const struct gsc_fmt *fmt, *def_fmt = NULL;
	unsigned int i;

	if (index >= ARRAY_SIZE(gsc_formats))
		return NULL;

	for (i = 0; i < ARRAY_SIZE(gsc_formats); ++i) {
		fmt = get_format(i);
		if (pixelformat && fmt->pixelformat == *pixelformat)
			return fmt;
		if (mbus_code && fmt->mbus_code == *mbus_code)
			return fmt;
		if (index == i)
			def_fmt = fmt;
	}
	return def_fmt;

}