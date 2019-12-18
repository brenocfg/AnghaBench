#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int resp_status; int /*<<< orphan*/  completion; } ;
struct TYPE_4__ {TYPE_1__ req; } ;
struct xen_drm_front_evtchnl {TYPE_2__ u; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int /*<<< orphan*/  XEN_DRM_FRONT_WAIT_BACK_MS ; 
 int /*<<< orphan*/  msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 scalar_t__ wait_for_completion_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int be_stream_wait_io(struct xen_drm_front_evtchnl *evtchnl)
{
	if (wait_for_completion_timeout(&evtchnl->u.req.completion,
			msecs_to_jiffies(XEN_DRM_FRONT_WAIT_BACK_MS)) <= 0)
		return -ETIMEDOUT;

	return evtchnl->u.req.resp_status;
}