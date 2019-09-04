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

__attribute__((used)) static inline int
sin_mul(int degrees, int factor)
{
	if (degrees > 180) {
		degrees -= 180;
		factor *= -1;
	}
	return factor * 4 * degrees * (180 - degrees) /
		(40500 - degrees * (180 - degrees));
}