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
struct vmmdev_write_core_dump {int /*<<< orphan*/  flags; } ;
struct vbg_session {int /*<<< orphan*/  requestor; } ;
struct TYPE_6__ {int /*<<< orphan*/  rc; } ;
struct TYPE_4__ {int /*<<< orphan*/  flags; } ;
struct TYPE_5__ {TYPE_1__ in; } ;
struct vbg_ioctl_write_coredump {TYPE_3__ hdr; TYPE_2__ u; } ;
struct vbg_dev {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  VMMDEVREQ_WRITE_COREDUMP ; 
 scalar_t__ vbg_ioctl_chk (TYPE_3__*,int,int /*<<< orphan*/ ) ; 
 struct vmmdev_write_core_dump* vbg_req_alloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vbg_req_free (struct vmmdev_write_core_dump*,int) ; 
 int /*<<< orphan*/  vbg_req_perform (struct vbg_dev*,struct vmmdev_write_core_dump*) ; 

__attribute__((used)) static int vbg_ioctl_write_core_dump(struct vbg_dev *gdev,
				     struct vbg_session *session,
				     struct vbg_ioctl_write_coredump *dump)
{
	struct vmmdev_write_core_dump *req;

	if (vbg_ioctl_chk(&dump->hdr, sizeof(dump->u.in), 0))
		return -EINVAL;

	req = vbg_req_alloc(sizeof(*req), VMMDEVREQ_WRITE_COREDUMP,
			    session->requestor);
	if (!req)
		return -ENOMEM;

	req->flags = dump->u.in.flags;
	dump->hdr.rc = vbg_req_perform(gdev, req);

	vbg_req_free(req, sizeof(*req));
	return 0;
}