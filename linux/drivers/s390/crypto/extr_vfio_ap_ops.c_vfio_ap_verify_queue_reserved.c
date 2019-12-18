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
struct vfio_ap_queue_reserved {unsigned long* apid; unsigned long* apqi; int reserved; } ;
struct TYPE_4__ {TYPE_1__* vfio_ap_drv; } ;
struct TYPE_3__ {int /*<<< orphan*/  driver; } ;

/* Variables and functions */
 int EADDRNOTAVAIL ; 
 int driver_for_each_device (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct vfio_ap_queue_reserved*,int /*<<< orphan*/ ) ; 
 TYPE_2__* matrix_dev ; 
 int /*<<< orphan*/  vfio_ap_has_queue ; 

__attribute__((used)) static int vfio_ap_verify_queue_reserved(unsigned long *apid,
					 unsigned long *apqi)
{
	int ret;
	struct vfio_ap_queue_reserved qres;

	qres.apid = apid;
	qres.apqi = apqi;
	qres.reserved = false;

	ret = driver_for_each_device(&matrix_dev->vfio_ap_drv->driver, NULL,
				     &qres, vfio_ap_has_queue);
	if (ret)
		return ret;

	if (qres.reserved)
		return 0;

	return -EADDRNOTAVAIL;
}