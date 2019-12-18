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
 int ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int find_closest (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  si1133_scale_available ; 

__attribute__((used)) static int si1133_scale_to_swgain(int scale_integer, int scale_fractional)
{
	scale_integer = find_closest(scale_integer, si1133_scale_available,
				     ARRAY_SIZE(si1133_scale_available));
	if (scale_integer < 0 ||
	    scale_integer > ARRAY_SIZE(si1133_scale_available) ||
	    scale_fractional != 0)
		return -EINVAL;

	return scale_integer;
}