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
struct msm_kms {struct msm_gem_address_space* aspace; } ;
struct msm_gem_address_space {TYPE_2__* mmu; } ;
struct mdp5_kms {int num_hwmixers; int num_hwpipes; int /*<<< orphan*/ * hwpipes; int /*<<< orphan*/ * hwmixers; } ;
struct TYPE_4__ {TYPE_1__* funcs; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* detach ) (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iommu_ports ; 
 int /*<<< orphan*/  mdp5_mixer_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mdp5_pipe_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msm_gem_address_space_put (struct msm_gem_address_space*) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct mdp5_kms* to_mdp5_kms (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  to_mdp_kms (struct msm_kms*) ; 

__attribute__((used)) static void mdp5_kms_destroy(struct msm_kms *kms)
{
	struct mdp5_kms *mdp5_kms = to_mdp5_kms(to_mdp_kms(kms));
	struct msm_gem_address_space *aspace = kms->aspace;
	int i;

	for (i = 0; i < mdp5_kms->num_hwmixers; i++)
		mdp5_mixer_destroy(mdp5_kms->hwmixers[i]);

	for (i = 0; i < mdp5_kms->num_hwpipes; i++)
		mdp5_pipe_destroy(mdp5_kms->hwpipes[i]);

	if (aspace) {
		aspace->mmu->funcs->detach(aspace->mmu,
				iommu_ports, ARRAY_SIZE(iommu_ports));
		msm_gem_address_space_put(aspace);
	}
}