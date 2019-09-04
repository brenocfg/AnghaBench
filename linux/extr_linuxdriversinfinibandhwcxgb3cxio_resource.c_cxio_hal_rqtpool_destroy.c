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
struct cxio_rdev {int /*<<< orphan*/  rqt_pool; } ;

/* Variables and functions */
 int /*<<< orphan*/  gen_pool_destroy (int /*<<< orphan*/ ) ; 

void cxio_hal_rqtpool_destroy(struct cxio_rdev *rdev_p)
{
	gen_pool_destroy(rdev_p->rqt_pool);
}