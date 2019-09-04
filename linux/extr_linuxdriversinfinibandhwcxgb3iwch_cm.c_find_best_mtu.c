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
struct t3c_data {int nmtus; unsigned short* mtus; } ;

/* Variables and functions */

__attribute__((used)) static unsigned int find_best_mtu(const struct t3c_data *d, unsigned short mtu)
{
	int i = 0;

	while (i < d->nmtus - 1 && d->mtus[i + 1] <= mtu)
		++i;
	return i;
}