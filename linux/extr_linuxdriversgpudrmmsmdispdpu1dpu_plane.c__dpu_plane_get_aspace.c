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
struct msm_gem_address_space {int dummy; } ;
struct dpu_plane_state {int dummy; } ;
struct dpu_plane {int /*<<< orphan*/  base; } ;
struct TYPE_2__ {struct msm_gem_address_space* aspace; } ;
struct dpu_kms {TYPE_1__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPU_ERROR (char*) ; 
 int EINVAL ; 
 struct dpu_kms* _dpu_plane_get_kms (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int _dpu_plane_get_aspace(
		struct dpu_plane *pdpu,
		struct dpu_plane_state *pstate,
		struct msm_gem_address_space **aspace)
{
	struct dpu_kms *kms;

	if (!pdpu || !pstate || !aspace) {
		DPU_ERROR("invalid parameters\n");
		return -EINVAL;
	}

	kms = _dpu_plane_get_kms(&pdpu->base);
	if (!kms) {
		DPU_ERROR("invalid kms\n");
		return -EINVAL;
	}

	*aspace = kms->base.aspace;

	return 0;
}