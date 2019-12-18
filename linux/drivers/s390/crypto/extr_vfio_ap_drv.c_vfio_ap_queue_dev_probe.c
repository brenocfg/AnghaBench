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
struct vfio_ap_queue {int /*<<< orphan*/  saved_isc; int /*<<< orphan*/  apqn; } ;
struct ap_device {int /*<<< orphan*/  device; } ;
struct TYPE_2__ {int /*<<< orphan*/  qid; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  VFIO_AP_ISC_INVALID ; 
 int /*<<< orphan*/  dev_set_drvdata (int /*<<< orphan*/ *,struct vfio_ap_queue*) ; 
 struct vfio_ap_queue* kzalloc (int,int /*<<< orphan*/ ) ; 
 TYPE_1__* to_ap_queue (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int vfio_ap_queue_dev_probe(struct ap_device *apdev)
{
	struct vfio_ap_queue *q;

	q = kzalloc(sizeof(*q), GFP_KERNEL);
	if (!q)
		return -ENOMEM;
	dev_set_drvdata(&apdev->device, q);
	q->apqn = to_ap_queue(&apdev->device)->qid;
	q->saved_isc = VFIO_AP_ISC_INVALID;
	return 0;
}