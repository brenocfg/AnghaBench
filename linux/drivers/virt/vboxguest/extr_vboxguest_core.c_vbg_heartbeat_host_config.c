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
struct vmmdev_heartbeat {int enabled; scalar_t__ interval_ns; } ;
struct vbg_dev {scalar_t__ heartbeat_interval_ms; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  VBG_KERNEL_REQUEST ; 
 int /*<<< orphan*/  VMMDEVREQ_HEARTBEAT_CONFIGURE ; 
 int /*<<< orphan*/  do_div (scalar_t__,int) ; 
 struct vmmdev_heartbeat* vbg_req_alloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vbg_req_free (struct vmmdev_heartbeat*,int) ; 
 int vbg_req_perform (struct vbg_dev*,struct vmmdev_heartbeat*) ; 
 int vbg_status_code_to_errno (int) ; 

__attribute__((used)) static int vbg_heartbeat_host_config(struct vbg_dev *gdev, bool enabled)
{
	struct vmmdev_heartbeat *req;
	int rc;

	req = vbg_req_alloc(sizeof(*req), VMMDEVREQ_HEARTBEAT_CONFIGURE,
			    VBG_KERNEL_REQUEST);
	if (!req)
		return -ENOMEM;

	req->enabled = enabled;
	req->interval_ns = 0;
	rc = vbg_req_perform(gdev, req);
	do_div(req->interval_ns, 1000000); /* ns -> ms */
	gdev->heartbeat_interval_ms = req->interval_ns;
	vbg_req_free(req, sizeof(*req));

	return vbg_status_code_to_errno(rc);
}