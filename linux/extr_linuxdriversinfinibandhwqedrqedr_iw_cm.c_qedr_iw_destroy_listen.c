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
struct qedr_iw_listener {scalar_t__ qed_handle; } ;
struct qedr_dev {int /*<<< orphan*/  rdma_ctx; TYPE_1__* ops; } ;
struct iw_cm_id {int /*<<< orphan*/  (* rem_ref ) (struct iw_cm_id*) ;int /*<<< orphan*/  device; struct qedr_iw_listener* provider_data; } ;
struct TYPE_2__ {int (* iwarp_destroy_listen ) (int /*<<< orphan*/ ,scalar_t__) ;} ;

/* Variables and functions */
 struct qedr_dev* get_qedr_dev (int /*<<< orphan*/ ) ; 
 int stub1 (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  stub2 (struct iw_cm_id*) ; 

int qedr_iw_destroy_listen(struct iw_cm_id *cm_id)
{
	struct qedr_iw_listener *listener = cm_id->provider_data;
	struct qedr_dev *dev = get_qedr_dev(cm_id->device);
	int rc = 0;

	if (listener->qed_handle)
		rc = dev->ops->iwarp_destroy_listen(dev->rdma_ctx,
						    listener->qed_handle);

	cm_id->rem_ref(cm_id);
	return rc;
}