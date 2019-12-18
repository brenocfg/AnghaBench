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

/* Variables and functions */
 scalar_t__ __is_raid10_offset (int) ; 
 int __raid10_far_copies (int) ; 
 int __raid10_near_copies (int) ; 

__attribute__((used)) static const char *raid10_md_layout_to_format(int layout)
{
	/*
	 * Bit 16 stands for "offset"
	 * (i.e. adjacent stripes hold copies)
	 *
	 * Refer to MD's raid10.c for details
	 */
	if (__is_raid10_offset(layout))
		return "offset";

	if (__raid10_near_copies(layout) > 1)
		return "near";

	if (__raid10_far_copies(layout) > 1)
		return "far";

	return "unknown";
}