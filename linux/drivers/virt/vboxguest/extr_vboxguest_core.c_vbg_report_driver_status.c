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
struct vmmdev_guest_status {scalar_t__ flags; int /*<<< orphan*/  status; int /*<<< orphan*/  facility; } ;
struct vbg_dev {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  VBG_KERNEL_REQUEST ; 
 int /*<<< orphan*/  VBOXGUEST_FACILITY_STATUS_ACTIVE ; 
 int /*<<< orphan*/  VBOXGUEST_FACILITY_STATUS_INACTIVE ; 
 int /*<<< orphan*/  VBOXGUEST_FACILITY_TYPE_VBOXGUEST_DRIVER ; 
 int VERR_NOT_IMPLEMENTED ; 
 int VINF_SUCCESS ; 
 int /*<<< orphan*/  VMMDEVREQ_REPORT_GUEST_STATUS ; 
 struct vmmdev_guest_status* vbg_req_alloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vbg_req_free (struct vmmdev_guest_status*,int) ; 
 int vbg_req_perform (struct vbg_dev*,struct vmmdev_guest_status*) ; 
 int vbg_status_code_to_errno (int) ; 

__attribute__((used)) static int vbg_report_driver_status(struct vbg_dev *gdev, bool active)
{
	struct vmmdev_guest_status *req;
	int rc;

	req = vbg_req_alloc(sizeof(*req), VMMDEVREQ_REPORT_GUEST_STATUS,
			    VBG_KERNEL_REQUEST);
	if (!req)
		return -ENOMEM;

	req->facility = VBOXGUEST_FACILITY_TYPE_VBOXGUEST_DRIVER;
	if (active)
		req->status = VBOXGUEST_FACILITY_STATUS_ACTIVE;
	else
		req->status = VBOXGUEST_FACILITY_STATUS_INACTIVE;
	req->flags = 0;

	rc = vbg_req_perform(gdev, req);
	if (rc == VERR_NOT_IMPLEMENTED)	/* Compatibility with older hosts. */
		rc = VINF_SUCCESS;

	vbg_req_free(req, sizeof(*req));

	return vbg_status_code_to_errno(rc);
}