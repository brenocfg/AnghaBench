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
struct input_mt_pos {scalar_t__ x; scalar_t__ y; } ;

/* Variables and functions */
 int MAX_TOUCHES ; 

__attribute__((used)) static int alps_get_mt_count(struct input_mt_pos *mt)
{
	int i, fingers = 0;

	for (i = 0; i < MAX_TOUCHES; i++) {
		if (mt[i].x != 0 || mt[i].y != 0)
			fingers++;
	}

	return fingers;
}