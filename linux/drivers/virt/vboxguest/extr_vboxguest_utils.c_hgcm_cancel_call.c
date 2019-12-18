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
struct TYPE_3__ {int /*<<< orphan*/  request_type; } ;
struct TYPE_4__ {int /*<<< orphan*/  flags; TYPE_1__ header; } ;
struct vmmdev_hgcm_call {TYPE_2__ header; int /*<<< orphan*/  phys_req_to_cancel; } ;
struct vbg_dev {int /*<<< orphan*/  cancel_req_mutex; struct vmmdev_hgcm_call* cancel_req; } ;

/* Variables and functions */
 int VERR_INVALID_PARAMETER ; 
 int VERR_NOT_FOUND ; 
 int VERR_NOT_IMPLEMENTED ; 
 int /*<<< orphan*/  VMMDEVREQ_HGCM_CANCEL ; 
 int /*<<< orphan*/  VMMDEV_HGCM_REQ_CANCELLED ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int vbg_req_perform (struct vbg_dev*,struct vmmdev_hgcm_call*) ; 
 int /*<<< orphan*/  virt_to_phys (struct vmmdev_hgcm_call*) ; 

__attribute__((used)) static int hgcm_cancel_call(struct vbg_dev *gdev, struct vmmdev_hgcm_call *call)
{
	int rc;

	/*
	 * We use a pre-allocated request for cancellations, which is
	 * protected by cancel_req_mutex. This means that all cancellations
	 * get serialized, this should be fine since they should be rare.
	 */
	mutex_lock(&gdev->cancel_req_mutex);
	gdev->cancel_req->phys_req_to_cancel = virt_to_phys(call);
	rc = vbg_req_perform(gdev, gdev->cancel_req);
	mutex_unlock(&gdev->cancel_req_mutex);

	if (rc == VERR_NOT_IMPLEMENTED) {
		call->header.flags |= VMMDEV_HGCM_REQ_CANCELLED;
		call->header.header.request_type = VMMDEVREQ_HGCM_CANCEL;

		rc = vbg_req_perform(gdev, call);
		if (rc == VERR_INVALID_PARAMETER)
			rc = VERR_NOT_FOUND;
	}

	if (rc >= 0)
		call->header.flags |= VMMDEV_HGCM_REQ_CANCELLED;

	return rc;
}