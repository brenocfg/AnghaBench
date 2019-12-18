#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ib_pd {int /*<<< orphan*/  usecnt; } ;
struct ib_fmr {TYPE_2__* device; struct ib_pd* pd; } ;
struct TYPE_3__ {int (* dealloc_fmr ) (struct ib_fmr*) ;} ;
struct TYPE_4__ {TYPE_1__ ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int stub1 (struct ib_fmr*) ; 

int ib_dealloc_fmr(struct ib_fmr *fmr)
{
	struct ib_pd *pd;
	int ret;

	pd = fmr->pd;
	ret = fmr->device->ops.dealloc_fmr(fmr);
	if (!ret)
		atomic_dec(&pd->usecnt);

	return ret;
}