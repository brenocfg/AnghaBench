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
struct drm_crtc {int dummy; } ;
struct dpu_crtc {int /*<<< orphan*/  frame_done_comp; int /*<<< orphan*/  frame_pending; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPU_ATRACE_BEGIN (char*) ; 
 int /*<<< orphan*/  DPU_ATRACE_END (char*) ; 
 int /*<<< orphan*/  DPU_DEBUG (char*) ; 
 int /*<<< orphan*/  DPU_ERROR (char*) ; 
 int /*<<< orphan*/  DPU_FRAME_DONE_TIMEOUT ; 
 int /*<<< orphan*/  DRM_ERROR (char*,int) ; 
 int EINVAL ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 struct dpu_crtc* to_dpu_crtc (struct drm_crtc*) ; 
 int wait_for_completion_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int _dpu_crtc_wait_for_frame_done(struct drm_crtc *crtc)
{
	struct dpu_crtc *dpu_crtc;
	int ret, rc = 0;

	if (!crtc) {
		DPU_ERROR("invalid argument\n");
		return -EINVAL;
	}
	dpu_crtc = to_dpu_crtc(crtc);

	if (!atomic_read(&dpu_crtc->frame_pending)) {
		DPU_DEBUG("no frames pending\n");
		return 0;
	}

	DPU_ATRACE_BEGIN("frame done completion wait");
	ret = wait_for_completion_timeout(&dpu_crtc->frame_done_comp,
			msecs_to_jiffies(DPU_FRAME_DONE_TIMEOUT));
	if (!ret) {
		DRM_ERROR("frame done wait timed out, ret:%d\n", ret);
		rc = -ETIMEDOUT;
	}
	DPU_ATRACE_END("frame done completion wait");

	return rc;
}