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
struct rect {int width; int height; } ;

/* Variables and functions */

__attribute__((used)) static bool are_rect_integer_multiples(struct rect src, struct rect dest)
{
	if (dest.width  >= src.width  && dest.width  % src.width  == 0 &&
		dest.height >= src.height && dest.height % src.height == 0)
		return true;

	return false;
}