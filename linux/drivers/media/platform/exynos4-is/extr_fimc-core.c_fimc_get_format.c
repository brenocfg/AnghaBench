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
struct fimc_fmt {int dummy; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (struct fimc_fmt*) ; 
 struct fimc_fmt* fimc_formats ; 

struct fimc_fmt *fimc_get_format(unsigned int index)
{
	if (index >= ARRAY_SIZE(fimc_formats))
		return NULL;

	return &fimc_formats[index];
}