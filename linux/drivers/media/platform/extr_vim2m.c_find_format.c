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
struct vim2m_fmt {scalar_t__ fourcc; } ;

/* Variables and functions */
 unsigned int NUM_FORMATS ; 
 struct vim2m_fmt* formats ; 

__attribute__((used)) static struct vim2m_fmt *find_format(u32 fourcc)
{
	struct vim2m_fmt *fmt;
	unsigned int k;

	for (k = 0; k < NUM_FORMATS; k++) {
		fmt = &formats[k];
		if (fmt->fourcc == fourcc)
			break;
	}

	if (k == NUM_FORMATS)
		return NULL;

	return &formats[k];
}