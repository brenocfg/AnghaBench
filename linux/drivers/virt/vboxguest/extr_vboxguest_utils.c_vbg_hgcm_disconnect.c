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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {int result; scalar_t__ flags; } ;
struct vmmdev_hgcm_disconnect {TYPE_1__ header; int /*<<< orphan*/  client_id; } ;
struct vbg_dev {int /*<<< orphan*/  hgcm_wq; } ;

/* Variables and functions */
 int ENOMEM ; 
 int VINF_HGCM_ASYNC_EXECUTE ; 
 int /*<<< orphan*/  VMMDEVREQ_HGCM_DISCONNECT ; 
 int /*<<< orphan*/  hgcm_req_done (struct vbg_dev*,TYPE_1__*) ; 
 struct vmmdev_hgcm_disconnect* vbg_req_alloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vbg_req_free (struct vmmdev_hgcm_disconnect*,int) ; 
 int vbg_req_perform (struct vbg_dev*,struct vmmdev_hgcm_disconnect*) ; 
 int /*<<< orphan*/  wait_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int vbg_hgcm_disconnect(struct vbg_dev *gdev, u32 requestor,
			u32 client_id, int *vbox_status)
{
	struct vmmdev_hgcm_disconnect *hgcm_disconnect = NULL;
	int rc;

	hgcm_disconnect = vbg_req_alloc(sizeof(*hgcm_disconnect),
					VMMDEVREQ_HGCM_DISCONNECT,
					requestor);
	if (!hgcm_disconnect)
		return -ENOMEM;

	hgcm_disconnect->header.flags = 0;
	hgcm_disconnect->client_id = client_id;

	rc = vbg_req_perform(gdev, hgcm_disconnect);

	if (rc == VINF_HGCM_ASYNC_EXECUTE)
		wait_event(gdev->hgcm_wq,
			   hgcm_req_done(gdev, &hgcm_disconnect->header));

	if (rc >= 0)
		rc = hgcm_disconnect->header.result;

	vbg_req_free(hgcm_disconnect, sizeof(*hgcm_disconnect));

	*vbox_status = rc;
	return 0;
}