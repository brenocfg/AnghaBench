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
struct unicam_fmt {scalar_t__ code; int depth; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (struct unicam_fmt*) ; 
 struct unicam_fmt* formats ; 

__attribute__((used)) static int find_mbus_depth_by_code(u32 code)
{
	const struct unicam_fmt *fmt;
	unsigned int k;

	for (k = 0; k < ARRAY_SIZE(formats); k++) {
		fmt = &formats[k];
		if (fmt->code == code)
			return fmt->depth;
	}

	return 0;
}