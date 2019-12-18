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
struct hantro_fmt {scalar_t__ fourcc; } ;

/* Variables and functions */

__attribute__((used)) static const struct hantro_fmt *
hantro_find_format(const struct hantro_fmt *formats, unsigned int num_fmts,
		   u32 fourcc)
{
	unsigned int i;

	for (i = 0; i < num_fmts; i++)
		if (formats[i].fourcc == fourcc)
			return &formats[i];
	return NULL;
}