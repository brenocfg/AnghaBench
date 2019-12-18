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
typedef  int u32 ;
struct vmmdev_hgcm_function_parameter {int dummy; } ;
struct TYPE_2__ {int result; } ;
struct vmmdev_hgcm_call {TYPE_1__ header; } ;
struct vbg_dev {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  VMMDEVREQ_HGCM_CALL ; 
 int hgcm_call_copy_back_result (struct vmmdev_hgcm_call*,struct vmmdev_hgcm_function_parameter*,int,void**) ; 
 int /*<<< orphan*/  hgcm_call_init_call (struct vmmdev_hgcm_call*,int,int,struct vmmdev_hgcm_function_parameter*,int,void**) ; 
 int hgcm_call_preprocess (struct vmmdev_hgcm_function_parameter*,int,void***,size_t*) ; 
 int /*<<< orphan*/  kfree (void**) ; 
 int /*<<< orphan*/  kvfree (void*) ; 
 int vbg_hgcm_do_call (struct vbg_dev*,struct vmmdev_hgcm_call*,int,int*) ; 
 struct vmmdev_hgcm_call* vbg_req_alloc (size_t,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vbg_req_free (struct vmmdev_hgcm_call*,size_t) ; 

int vbg_hgcm_call(struct vbg_dev *gdev, u32 requestor, u32 client_id,
		  u32 function, u32 timeout_ms,
		  struct vmmdev_hgcm_function_parameter *parms, u32 parm_count,
		  int *vbox_status)
{
	struct vmmdev_hgcm_call *call;
	void **bounce_bufs = NULL;
	bool leak_it;
	size_t size;
	int i, ret;

	size = sizeof(struct vmmdev_hgcm_call) +
		   parm_count * sizeof(struct vmmdev_hgcm_function_parameter);
	/*
	 * Validate and buffer the parameters for the call. This also increases
	 * call_size with the amount of extra space needed for page lists.
	 */
	ret = hgcm_call_preprocess(parms, parm_count, &bounce_bufs, &size);
	if (ret) {
		/* Even on error bounce bufs may still have been allocated */
		goto free_bounce_bufs;
	}

	call = vbg_req_alloc(size, VMMDEVREQ_HGCM_CALL, requestor);
	if (!call) {
		ret = -ENOMEM;
		goto free_bounce_bufs;
	}

	hgcm_call_init_call(call, client_id, function, parms, parm_count,
			    bounce_bufs);

	ret = vbg_hgcm_do_call(gdev, call, timeout_ms, &leak_it);
	if (ret == 0) {
		*vbox_status = call->header.result;
		ret = hgcm_call_copy_back_result(call, parms, parm_count,
						 bounce_bufs);
	}

	if (!leak_it)
		vbg_req_free(call, size);

free_bounce_bufs:
	if (bounce_bufs) {
		for (i = 0; i < parm_count; i++)
			kvfree(bounce_bufs[i]);
		kfree(bounce_bufs);
	}

	return ret;
}