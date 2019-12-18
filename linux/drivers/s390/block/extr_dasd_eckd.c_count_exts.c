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

__attribute__((used)) static int count_exts(unsigned int from, unsigned int to, int trks_per_ext)
{
	int cur_pos = 0;
	int count = 0;
	int tmp;

	if (from == to)
		return 1;

	/* Count first partial extent */
	if (from % trks_per_ext != 0) {
		tmp = from + trks_per_ext - (from % trks_per_ext) - 1;
		if (tmp > to)
			tmp = to;
		cur_pos = tmp - from + 1;
		count++;
	}
	/* Count full extents */
	if (to - (from + cur_pos) + 1 >= trks_per_ext) {
		tmp = to - ((to - trks_per_ext + 1) % trks_per_ext);
		count += (tmp - (from + cur_pos) + 1) / trks_per_ext;
		cur_pos = tmp;
	}
	/* Count last partial extent */
	if (cur_pos < to)
		count++;

	return count;
}