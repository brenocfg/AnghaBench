#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct msm_kms {struct msm_gem_address_space* aspace; } ;
struct msm_gem_address_space {TYPE_3__* mmu; } ;
struct mdp4_kms {scalar_t__ rpm_enabled; int /*<<< orphan*/  blank_cursor_bo; scalar_t__ blank_cursor_iova; TYPE_2__* dev; } ;
struct device {int dummy; } ;
struct TYPE_6__ {TYPE_1__* funcs; } ;
struct TYPE_5__ {struct device* dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* detach ) (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_gem_object_put_unlocked (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iommu_ports ; 
 int /*<<< orphan*/  kfree (struct mdp4_kms*) ; 
 int /*<<< orphan*/  msm_gem_address_space_put (struct msm_gem_address_space*) ; 
 int /*<<< orphan*/  msm_gem_unpin_iova (int /*<<< orphan*/ ,struct msm_gem_address_space*) ; 
 int /*<<< orphan*/  pm_runtime_disable (struct device*) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct mdp4_kms* to_mdp4_kms (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  to_mdp_kms (struct msm_kms*) ; 

__attribute__((used)) static void mdp4_destroy(struct msm_kms *kms)
{
	struct mdp4_kms *mdp4_kms = to_mdp4_kms(to_mdp_kms(kms));
	struct device *dev = mdp4_kms->dev->dev;
	struct msm_gem_address_space *aspace = kms->aspace;

	if (mdp4_kms->blank_cursor_iova)
		msm_gem_unpin_iova(mdp4_kms->blank_cursor_bo, kms->aspace);
	drm_gem_object_put_unlocked(mdp4_kms->blank_cursor_bo);

	if (aspace) {
		aspace->mmu->funcs->detach(aspace->mmu,
				iommu_ports, ARRAY_SIZE(iommu_ports));
		msm_gem_address_space_put(aspace);
	}

	if (mdp4_kms->rpm_enabled)
		pm_runtime_disable(dev);

	kfree(mdp4_kms);
}