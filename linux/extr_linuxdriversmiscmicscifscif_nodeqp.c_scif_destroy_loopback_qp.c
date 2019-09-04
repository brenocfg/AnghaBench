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
struct scif_dev {int /*<<< orphan*/ * sdev; TYPE_3__* qpairs; } ;
struct TYPE_4__ {TYPE_3__* rb_base; } ;
struct TYPE_6__ {TYPE_1__ outbound_q; } ;
struct TYPE_5__ {int /*<<< orphan*/ * loopb_dev; int /*<<< orphan*/  loopb_wq; } ;

/* Variables and functions */
 int /*<<< orphan*/  destroy_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (TYPE_3__*) ; 
 int /*<<< orphan*/  scif_destroy_intr_wq (struct scif_dev*) ; 
 TYPE_2__ scif_info ; 
 int /*<<< orphan*/  scif_peer_unregister_device (struct scif_dev*) ; 

int scif_destroy_loopback_qp(struct scif_dev *scifdev)
{
	scif_peer_unregister_device(scifdev);
	destroy_workqueue(scif_info.loopb_wq);
	scif_destroy_intr_wq(scifdev);
	kfree(scifdev->qpairs->outbound_q.rb_base);
	kfree(scifdev->qpairs);
	scifdev->sdev = NULL;
	scif_info.loopb_dev = NULL;
	return 0;
}