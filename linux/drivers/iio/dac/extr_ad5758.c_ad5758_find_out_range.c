#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int min; int max; int /*<<< orphan*/  reg; } ;
struct ad5758_state {TYPE_1__ out_range; } ;
struct ad5758_range {int min; int max; int /*<<< orphan*/  reg; } ;

/* Variables and functions */
 int EINVAL ; 

__attribute__((used)) static int ad5758_find_out_range(struct ad5758_state *st,
				 const struct ad5758_range *range,
				 unsigned int size,
				 int min, int max)
{
	int i;

	for (i = 0; i < size; i++) {
		if ((min == range[i].min) && (max == range[i].max)) {
			st->out_range.reg = range[i].reg;
			st->out_range.min = range[i].min;
			st->out_range.max = range[i].max;

			return 0;
		}
	}

	return -EINVAL;
}