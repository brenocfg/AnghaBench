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
struct TYPE_2__ {int /*<<< orphan*/  id; } ;
struct drm_encoder {TYPE_1__ base; } ;
struct drm_crtc_state {int dummy; } ;
struct dpu_rm_requirements {int /*<<< orphan*/  hw_res; int /*<<< orphan*/  topology; } ;
struct dpu_rm {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPU_ERROR (char*) ; 
 int _dpu_rm_reserve_ctls (struct dpu_rm*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int _dpu_rm_reserve_intf_related_hw (struct dpu_rm*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int _dpu_rm_reserve_lms (struct dpu_rm*,int /*<<< orphan*/ ,struct dpu_rm_requirements*) ; 

__attribute__((used)) static int _dpu_rm_make_reservation(
		struct dpu_rm *rm,
		struct drm_encoder *enc,
		struct drm_crtc_state *crtc_state,
		struct dpu_rm_requirements *reqs)
{
	int ret;

	ret = _dpu_rm_reserve_lms(rm, enc->base.id, reqs);
	if (ret) {
		DPU_ERROR("unable to find appropriate mixers\n");
		return ret;
	}

	ret = _dpu_rm_reserve_ctls(rm, enc->base.id, &reqs->topology);
	if (ret) {
		DPU_ERROR("unable to find appropriate CTL\n");
		return ret;
	}

	ret = _dpu_rm_reserve_intf_related_hw(rm, enc->base.id, &reqs->hw_res);
	if (ret)
		return ret;

	return ret;
}