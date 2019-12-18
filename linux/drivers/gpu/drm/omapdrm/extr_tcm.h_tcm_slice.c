#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int y; int x; } ;
struct TYPE_4__ {int y; scalar_t__ x; } ;
struct tcm_area {TYPE_3__* tcm; TYPE_2__ p1; TYPE_1__ p0; int /*<<< orphan*/  is2d; } ;
struct TYPE_6__ {int width; } ;

/* Variables and functions */

__attribute__((used)) static inline void tcm_slice(struct tcm_area *parent, struct tcm_area *slice)
{
	*slice = *parent;

	/* check if we need to slice */
	if (slice->tcm && !slice->is2d &&
		slice->p0.y != slice->p1.y &&
		(slice->p0.x || (slice->p1.x != slice->tcm->width - 1))) {
		/* set end point of slice (start always remains) */
		slice->p1.x = slice->tcm->width - 1;
		slice->p1.y = (slice->p0.x) ? slice->p0.y : slice->p1.y - 1;
		/* adjust remaining area */
		parent->p0.x = 0;
		parent->p0.y = slice->p1.y + 1;
	} else {
		/* mark this as the last slice */
		parent->tcm = NULL;
	}
}