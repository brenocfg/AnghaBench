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
struct bdisp_fmt {scalar_t__ pixelformat; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (struct bdisp_fmt*) ; 
 struct bdisp_fmt* bdisp_formats ; 

__attribute__((used)) static const struct bdisp_fmt *bdisp_find_fmt(u32 pixelformat)
{
	const struct bdisp_fmt *fmt;
	unsigned int i;

	for (i = 0; i < ARRAY_SIZE(bdisp_formats); i++) {
		fmt = &bdisp_formats[i];
		if (fmt->pixelformat == pixelformat)
			return fmt;
	}

	return NULL;
}