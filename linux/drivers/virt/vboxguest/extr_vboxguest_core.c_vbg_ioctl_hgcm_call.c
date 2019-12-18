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
struct vmmdev_hgcm_function_parameter32 {int /*<<< orphan*/  type; } ;
struct vmmdev_hgcm_function_parameter {int /*<<< orphan*/  type; } ;
struct vbg_session {int /*<<< orphan*/  requestor; int /*<<< orphan*/ * hgcm_client_ids; } ;
struct TYPE_2__ {int size_in; int size_out; int /*<<< orphan*/  rc; } ;
struct vbg_ioctl_hgcm_call {int parm_count; TYPE_1__ hdr; int /*<<< orphan*/  timeout_ms; int /*<<< orphan*/  function; int /*<<< orphan*/  client_id; } ;
struct vbg_dev {int /*<<< orphan*/  session_mutex; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CONFIG_COMPAT ; 
 int E2BIG ; 
 int EINTR ; 
 int EINVAL ; 
 int ETIMEDOUT ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  U32_MAX ; 
 struct vmmdev_hgcm_function_parameter* VBG_IOCTL_HGCM_CALL_PARMS (struct vbg_ioctl_hgcm_call*) ; 
 struct vmmdev_hgcm_function_parameter32* VBG_IOCTL_HGCM_CALL_PARMS32 (struct vbg_ioctl_hgcm_call*) ; 
 int /*<<< orphan*/  VERR_OUT_OF_RANGE ; 
 int VMMDEV_HGCM_MAX_PARMS ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vbg_debug (char*,size_t,...) ; 
 int /*<<< orphan*/  vbg_err (char*,int) ; 
 int vbg_hgcm_call (struct vbg_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct vmmdev_hgcm_function_parameter*,int,int /*<<< orphan*/ *) ; 
 int vbg_hgcm_call32 (struct vbg_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct vmmdev_hgcm_function_parameter32*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vbg_param_valid (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vbg_ioctl_hgcm_call(struct vbg_dev *gdev,
			       struct vbg_session *session, bool f32bit,
			       struct vbg_ioctl_hgcm_call *call)
{
	size_t actual_size;
	u32 client_id;
	int i, ret;

	if (call->hdr.size_in < sizeof(*call))
		return -EINVAL;

	if (call->hdr.size_in != call->hdr.size_out)
		return -EINVAL;

	if (call->parm_count > VMMDEV_HGCM_MAX_PARMS)
		return -E2BIG;

	client_id = call->client_id;
	if (client_id == 0 || client_id == U32_MAX)
		return -EINVAL;

	actual_size = sizeof(*call);
	if (f32bit)
		actual_size += call->parm_count *
			       sizeof(struct vmmdev_hgcm_function_parameter32);
	else
		actual_size += call->parm_count *
			       sizeof(struct vmmdev_hgcm_function_parameter);
	if (call->hdr.size_in < actual_size) {
		vbg_debug("VBG_IOCTL_HGCM_CALL: hdr.size_in %d required size is %zd\n",
			  call->hdr.size_in, actual_size);
		return -EINVAL;
	}
	call->hdr.size_out = actual_size;

	/* Validate parameter types */
	if (f32bit) {
		struct vmmdev_hgcm_function_parameter32 *parm =
			VBG_IOCTL_HGCM_CALL_PARMS32(call);

		for (i = 0; i < call->parm_count; i++)
			if (!vbg_param_valid(parm[i].type))
				return -EINVAL;
	} else {
		struct vmmdev_hgcm_function_parameter *parm =
			VBG_IOCTL_HGCM_CALL_PARMS(call);

		for (i = 0; i < call->parm_count; i++)
			if (!vbg_param_valid(parm[i].type))
				return -EINVAL;
	}

	/*
	 * Validate the client id.
	 */
	mutex_lock(&gdev->session_mutex);
	for (i = 0; i < ARRAY_SIZE(session->hgcm_client_ids); i++)
		if (session->hgcm_client_ids[i] == client_id)
			break;
	mutex_unlock(&gdev->session_mutex);
	if (i >= ARRAY_SIZE(session->hgcm_client_ids)) {
		vbg_debug("VBG_IOCTL_HGCM_CALL: INVALID handle. u32Client=%#08x\n",
			  client_id);
		return -EINVAL;
	}

	if (IS_ENABLED(CONFIG_COMPAT) && f32bit)
		ret = vbg_hgcm_call32(gdev, session->requestor, client_id,
				      call->function, call->timeout_ms,
				      VBG_IOCTL_HGCM_CALL_PARMS32(call),
				      call->parm_count, &call->hdr.rc);
	else
		ret = vbg_hgcm_call(gdev, session->requestor, client_id,
				    call->function, call->timeout_ms,
				    VBG_IOCTL_HGCM_CALL_PARMS(call),
				    call->parm_count, &call->hdr.rc);

	if (ret == -E2BIG) {
		/* E2BIG needs to be reported through the hdr.rc field. */
		call->hdr.rc = VERR_OUT_OF_RANGE;
		ret = 0;
	}

	if (ret && ret != -EINTR && ret != -ETIMEDOUT)
		vbg_err("VBG_IOCTL_HGCM_CALL error: %d\n", ret);

	return ret;
}