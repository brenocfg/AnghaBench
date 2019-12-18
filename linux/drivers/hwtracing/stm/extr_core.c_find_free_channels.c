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
 unsigned int ALIGN (unsigned int,unsigned int) ; 
 unsigned int find_next_zero_bit (unsigned long*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  test_bit (unsigned int,unsigned long*) ; 

__attribute__((used)) static int find_free_channels(unsigned long *bitmap, unsigned int start,
			      unsigned int end, unsigned int width)
{
	unsigned int pos;
	int i;

	for (pos = start; pos < end + 1; pos = ALIGN(pos, width)) {
		pos = find_next_zero_bit(bitmap, end + 1, pos);
		if (pos + width > end + 1)
			break;

		if (pos & (width - 1))
			continue;

		for (i = 1; i < width && !test_bit(pos + i, bitmap); i++)
			;
		if (i == width)
			return pos;

		/* step over [pos..pos+i) to continue search */
		pos += i;
	}

	return -1;
}