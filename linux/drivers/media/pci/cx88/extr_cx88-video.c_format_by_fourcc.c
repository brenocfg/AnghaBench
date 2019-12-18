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
struct cx8800_fmt {unsigned int fourcc; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (struct cx8800_fmt const*) ; 
 struct cx8800_fmt const* formats ; 

__attribute__((used)) static const struct cx8800_fmt *format_by_fourcc(unsigned int fourcc)
{
	unsigned int i;

	for (i = 0; i < ARRAY_SIZE(formats); i++)
		if (formats[i].fourcc == fourcc)
			return formats + i;
	return NULL;
}