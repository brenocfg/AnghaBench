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
struct aoedev {int ntargets; TYPE_1__** targets; } ;
struct TYPE_2__ {scalar_t__ taint; } ;

/* Variables and functions */

__attribute__((used)) static int
count_targets(struct aoedev *d, int *untainted)
{
	int i, good;

	for (i = good = 0; i < d->ntargets && d->targets[i]; ++i)
		if (d->targets[i]->taint == 0)
			good++;

	if (untainted)
		*untainted = good;
	return i;
}