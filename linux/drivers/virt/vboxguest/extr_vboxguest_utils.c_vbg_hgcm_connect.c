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
typedef  scalar_t__ u32 ;
struct vmmdev_hgcm_service_location {int dummy; } ;
struct TYPE_2__ {int result; scalar_t__ flags; } ;
struct vmmdev_hgcm_connect {TYPE_1__ header; scalar_t__ client_id; int /*<<< orphan*/  loc; } ;
struct vbg_dev {int /*<<< orphan*/  hgcm_wq; } ;

/* Variables and functions */
 int ENOMEM ; 
 int VINF_HGCM_ASYNC_EXECUTE ; 
 int /*<<< orphan*/  VMMDEVREQ_HGCM_CONNECT ; 
 int /*<<< orphan*/  hgcm_req_done (struct vbg_dev*,TYPE_1__*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct vmmdev_hgcm_service_location*,int) ; 
 struct vmmdev_hgcm_connect* vbg_req_alloc (int,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  vbg_req_free (struct vmmdev_hgcm_connect*,int) ; 
 int vbg_req_perform (struct vbg_dev*,struct vmmdev_hgcm_connect*) ; 
 int /*<<< orphan*/  wait_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int vbg_hgcm_connect(struct vbg_dev *gdev, u32 requestor,
		     struct vmmdev_hgcm_service_location *loc,
		     u32 *client_id, int *vbox_status)
{
	struct vmmdev_hgcm_connect *hgcm_connect = NULL;
	int rc;

	hgcm_connect = vbg_req_alloc(sizeof(*hgcm_connect),
				     VMMDEVREQ_HGCM_CONNECT, requestor);
	if (!hgcm_connect)
		return -ENOMEM;

	hgcm_connect->header.flags = 0;
	memcpy(&hgcm_connect->loc, loc, sizeof(*loc));
	hgcm_connect->client_id = 0;

	rc = vbg_req_perform(gdev, hgcm_connect);

	if (rc == VINF_HGCM_ASYNC_EXECUTE)
		wait_event(gdev->hgcm_wq,
			   hgcm_req_done(gdev, &hgcm_connect->header));

	if (rc >= 0) {
		*client_id = hgcm_connect->client_id;
		rc = hgcm_connect->header.result;
	}

	vbg_req_free(hgcm_connect, sizeof(*hgcm_connect));

	*vbox_status = rc;
	return 0;
}