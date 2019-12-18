#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  void* u32 ;
struct vbg_session {void** hgcm_client_ids; int /*<<< orphan*/  requestor; } ;
struct TYPE_6__ {void* client_id; } ;
struct TYPE_5__ {int /*<<< orphan*/  loc; } ;
struct TYPE_7__ {TYPE_2__ out; TYPE_1__ in; } ;
struct TYPE_8__ {scalar_t__ rc; } ;
struct vbg_ioctl_hgcm_connect {TYPE_3__ u; TYPE_4__ hdr; } ;
struct vbg_dev {int /*<<< orphan*/  session_mutex; } ;

/* Variables and functions */
 int ARRAY_SIZE (void**) ; 
 int EINVAL ; 
 int EMFILE ; 
 void* U32_MAX ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int vbg_hgcm_connect (struct vbg_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void**,scalar_t__*) ; 
 scalar_t__ vbg_ioctl_chk (TYPE_4__*,int,int) ; 

__attribute__((used)) static int vbg_ioctl_hgcm_connect(struct vbg_dev *gdev,
				  struct vbg_session *session,
				  struct vbg_ioctl_hgcm_connect *conn)
{
	u32 client_id;
	int i, ret;

	if (vbg_ioctl_chk(&conn->hdr, sizeof(conn->u.in), sizeof(conn->u.out)))
		return -EINVAL;

	/* Find a free place in the sessions clients array and claim it */
	mutex_lock(&gdev->session_mutex);
	for (i = 0; i < ARRAY_SIZE(session->hgcm_client_ids); i++) {
		if (!session->hgcm_client_ids[i]) {
			session->hgcm_client_ids[i] = U32_MAX;
			break;
		}
	}
	mutex_unlock(&gdev->session_mutex);

	if (i >= ARRAY_SIZE(session->hgcm_client_ids))
		return -EMFILE;

	ret = vbg_hgcm_connect(gdev, session->requestor, &conn->u.in.loc,
			       &client_id, &conn->hdr.rc);

	mutex_lock(&gdev->session_mutex);
	if (ret == 0 && conn->hdr.rc >= 0) {
		conn->u.out.client_id = client_id;
		session->hgcm_client_ids[i] = client_id;
	} else {
		conn->u.out.client_id = 0;
		session->hgcm_client_ids[i] = 0;
	}
	mutex_unlock(&gdev->session_mutex);

	return ret;
}