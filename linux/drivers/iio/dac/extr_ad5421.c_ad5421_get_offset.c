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
struct ad5421_state {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ad5421_get_current_min_max (struct ad5421_state*,unsigned int*,unsigned int*) ; 

__attribute__((used)) static inline unsigned int ad5421_get_offset(struct ad5421_state *st)
{
	unsigned int min, max;

	ad5421_get_current_min_max(st, &min, &max);
	return (min * (1 << 16)) / (max - min);
}