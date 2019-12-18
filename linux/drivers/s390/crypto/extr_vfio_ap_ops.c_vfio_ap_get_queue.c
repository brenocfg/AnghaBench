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
struct vfio_ap_queue {struct ap_matrix_mdev* matrix_mdev; } ;
struct device {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  aqm; int /*<<< orphan*/  apm; } ;
struct ap_matrix_mdev {TYPE_1__ matrix; } ;
struct TYPE_6__ {TYPE_2__* vfio_ap_drv; } ;
struct TYPE_5__ {int /*<<< orphan*/  driver; } ;

/* Variables and functions */
 int /*<<< orphan*/  AP_QID_CARD (int) ; 
 int /*<<< orphan*/  AP_QID_QUEUE (int) ; 
 struct vfio_ap_queue* dev_get_drvdata (struct device*) ; 
 struct device* driver_find_device (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  match_apqn ; 
 TYPE_3__* matrix_dev ; 
 int /*<<< orphan*/  put_device (struct device*) ; 
 int /*<<< orphan*/  test_bit_inv (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct vfio_ap_queue *vfio_ap_get_queue(
					struct ap_matrix_mdev *matrix_mdev,
					int apqn)
{
	struct vfio_ap_queue *q;
	struct device *dev;

	if (!test_bit_inv(AP_QID_CARD(apqn), matrix_mdev->matrix.apm))
		return NULL;
	if (!test_bit_inv(AP_QID_QUEUE(apqn), matrix_mdev->matrix.aqm))
		return NULL;

	dev = driver_find_device(&matrix_dev->vfio_ap_drv->driver, NULL,
				 &apqn, match_apqn);
	if (!dev)
		return NULL;
	q = dev_get_drvdata(dev);
	q->matrix_mdev = matrix_mdev;
	put_device(dev);

	return q;
}