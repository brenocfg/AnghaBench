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
typedef  int /*<<< orphan*/  u32 ;
struct ct_request {int /*<<< orphan*/  status; int /*<<< orphan*/  fence; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  done ; 
 scalar_t__ unlikely (int) ; 
 int wait_for (int /*<<< orphan*/ ,int) ; 
 int wait_for_us (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int wait_for_ct_request_update(struct ct_request *req, u32 *status)
{
	int err;

	/*
	 * Fast commands should complete in less than 10us, so sample quickly
	 * up to that length of time, then switch to a slower sleep-wait loop.
	 * No GuC command should ever take longer than 10ms.
	 */
#define done INTEL_GUC_MSG_IS_RESPONSE(READ_ONCE(req->status))
	err = wait_for_us(done, 10);
	if (err)
		err = wait_for(done, 10);
#undef done

	if (unlikely(err))
		DRM_ERROR("CT: fence %u err %d\n", req->fence, err);

	*status = req->status;
	return err;
}