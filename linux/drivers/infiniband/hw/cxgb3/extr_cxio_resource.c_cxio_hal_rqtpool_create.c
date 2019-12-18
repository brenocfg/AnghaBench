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
struct TYPE_2__ {unsigned long rqt_base; int rqt_top; } ;
struct cxio_rdev {scalar_t__ rqt_pool; TYPE_1__ rnic_info; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  MIN_RQT_SHIFT ; 
 int RQT_CHUNK ; 
 int /*<<< orphan*/  gen_pool_add (scalar_t__,unsigned long,int,int) ; 
 scalar_t__ gen_pool_create (int /*<<< orphan*/ ,int) ; 

int cxio_hal_rqtpool_create(struct cxio_rdev *rdev_p)
{
	unsigned long i;
	rdev_p->rqt_pool = gen_pool_create(MIN_RQT_SHIFT, -1);
	if (rdev_p->rqt_pool)
		for (i = rdev_p->rnic_info.rqt_base;
		     i <= rdev_p->rnic_info.rqt_top - RQT_CHUNK + 1;
		     i += RQT_CHUNK)
			gen_pool_add(rdev_p->rqt_pool, i, RQT_CHUNK, -1);
	return rdev_p->rqt_pool ? 0 : -ENOMEM;
}