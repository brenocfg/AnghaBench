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
struct cxio_rdev {TYPE_1__* t3cdev_p; int /*<<< orphan*/  rscp; int /*<<< orphan*/  entry; } ;
struct TYPE_2__ {int /*<<< orphan*/ * ulp; } ;

/* Variables and functions */
 int /*<<< orphan*/  cxio_hal_destroy_ctrl_qp (struct cxio_rdev*) ; 
 int /*<<< orphan*/  cxio_hal_destroy_resource (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cxio_hal_pblpool_destroy (struct cxio_rdev*) ; 
 int /*<<< orphan*/  cxio_hal_rqtpool_destroy (struct cxio_rdev*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 

void cxio_rdev_close(struct cxio_rdev *rdev_p)
{
	if (rdev_p) {
		cxio_hal_pblpool_destroy(rdev_p);
		cxio_hal_rqtpool_destroy(rdev_p);
		list_del(&rdev_p->entry);
		cxio_hal_destroy_ctrl_qp(rdev_p);
		cxio_hal_destroy_resource(rdev_p->rscp);
		rdev_p->t3cdev_p->ulp = NULL;
	}
}