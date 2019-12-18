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
struct vfio_ap_queue {scalar_t__ saved_isc; scalar_t__ saved_pfn; TYPE_1__* matrix_mdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  mdev; int /*<<< orphan*/  kvm; } ;

/* Variables and functions */
 scalar_t__ VFIO_AP_ISC_INVALID ; 
 int /*<<< orphan*/  kvm_s390_gisc_unregister (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  mdev_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfio_unpin_pages (int /*<<< orphan*/ ,scalar_t__*,int) ; 

__attribute__((used)) static void vfio_ap_free_aqic_resources(struct vfio_ap_queue *q)
{
	if (q->saved_isc != VFIO_AP_ISC_INVALID && q->matrix_mdev)
		kvm_s390_gisc_unregister(q->matrix_mdev->kvm, q->saved_isc);
	if (q->saved_pfn && q->matrix_mdev)
		vfio_unpin_pages(mdev_dev(q->matrix_mdev->mdev),
				 &q->saved_pfn, 1);
	q->saved_pfn = 0;
	q->saved_isc = VFIO_AP_ISC_INVALID;
}