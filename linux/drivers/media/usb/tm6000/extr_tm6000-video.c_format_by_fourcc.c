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
struct tm6000_fmt {unsigned int fourcc; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (struct tm6000_fmt*) ; 
 struct tm6000_fmt* format ; 

__attribute__((used)) static struct tm6000_fmt *format_by_fourcc(unsigned int fourcc)
{
	unsigned int i;

	for (i = 0; i < ARRAY_SIZE(format); i++)
		if (format[i].fourcc == fourcc)
			return format+i;
	return NULL;
}