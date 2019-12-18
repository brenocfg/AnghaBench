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
typedef  int uint32_t ;

/* Variables and functions */
 int utile_height (int) ; 
 int utile_width (int) ; 

__attribute__((used)) static bool
size_is_lt(uint32_t width, uint32_t height, int cpp)
{
	return (width <= 4 * utile_width(cpp) ||
		height <= 4 * utile_height(cpp));
}