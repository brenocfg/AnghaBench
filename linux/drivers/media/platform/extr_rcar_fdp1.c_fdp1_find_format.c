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
struct fdp1_fmt {scalar_t__ fourcc; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (struct fdp1_fmt*) ; 
 struct fdp1_fmt* fdp1_formats ; 

__attribute__((used)) static const struct fdp1_fmt *fdp1_find_format(u32 pixelformat)
{
	const struct fdp1_fmt *fmt;
	unsigned int i;

	for (i = 0; i < ARRAY_SIZE(fdp1_formats); i++) {
		fmt = &fdp1_formats[i];
		if (fmt->fourcc == pixelformat)
			return fmt;
	}

	return NULL;
}