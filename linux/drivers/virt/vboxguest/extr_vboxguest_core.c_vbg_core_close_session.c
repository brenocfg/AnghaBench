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
struct vbg_session {int /*<<< orphan*/ * hgcm_client_ids; struct vbg_dev* gdev; } ;
struct vbg_dev {int dummy; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  U32_MAX ; 
 int /*<<< orphan*/  VBG_KERNEL_REQUEST ; 
 int /*<<< orphan*/  kfree (struct vbg_session*) ; 
 int /*<<< orphan*/  vbg_hgcm_disconnect (struct vbg_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  vbg_set_session_capabilities (struct vbg_dev*,struct vbg_session*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vbg_set_session_event_filter (struct vbg_dev*,struct vbg_session*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void vbg_core_close_session(struct vbg_session *session)
{
	struct vbg_dev *gdev = session->gdev;
	int i, rc;

	vbg_set_session_capabilities(gdev, session, 0, U32_MAX, true);
	vbg_set_session_event_filter(gdev, session, 0, U32_MAX, true);

	for (i = 0; i < ARRAY_SIZE(session->hgcm_client_ids); i++) {
		if (!session->hgcm_client_ids[i])
			continue;

		/* requestor is kernel here, as we're cleaning up. */
		vbg_hgcm_disconnect(gdev, VBG_KERNEL_REQUEST,
				    session->hgcm_client_ids[i], &rc);
	}

	kfree(session);
}