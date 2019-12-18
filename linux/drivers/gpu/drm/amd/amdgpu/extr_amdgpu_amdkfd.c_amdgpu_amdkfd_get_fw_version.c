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
typedef  int /*<<< orphan*/  uint32_t ;
struct kgd_dev {int dummy; } ;
struct TYPE_5__ {TYPE_1__* instance; } ;
struct TYPE_6__ {int /*<<< orphan*/  rlc_fw_version; int /*<<< orphan*/  mec2_fw_version; int /*<<< orphan*/  mec_fw_version; int /*<<< orphan*/  ce_fw_version; int /*<<< orphan*/  me_fw_version; int /*<<< orphan*/  pfp_fw_version; } ;
struct amdgpu_device {TYPE_2__ sdma; TYPE_3__ gfx; } ;
typedef  enum kgd_engine_type { ____Placeholder_kgd_engine_type } kgd_engine_type ;
struct TYPE_4__ {int /*<<< orphan*/  fw_version; } ;

/* Variables and functions */
#define  KGD_ENGINE_CE 135 
#define  KGD_ENGINE_ME 134 
#define  KGD_ENGINE_MEC1 133 
#define  KGD_ENGINE_MEC2 132 
#define  KGD_ENGINE_PFP 131 
#define  KGD_ENGINE_RLC 130 
#define  KGD_ENGINE_SDMA1 129 
#define  KGD_ENGINE_SDMA2 128 

uint32_t amdgpu_amdkfd_get_fw_version(struct kgd_dev *kgd,
				      enum kgd_engine_type type)
{
	struct amdgpu_device *adev = (struct amdgpu_device *)kgd;

	switch (type) {
	case KGD_ENGINE_PFP:
		return adev->gfx.pfp_fw_version;

	case KGD_ENGINE_ME:
		return adev->gfx.me_fw_version;

	case KGD_ENGINE_CE:
		return adev->gfx.ce_fw_version;

	case KGD_ENGINE_MEC1:
		return adev->gfx.mec_fw_version;

	case KGD_ENGINE_MEC2:
		return adev->gfx.mec2_fw_version;

	case KGD_ENGINE_RLC:
		return adev->gfx.rlc_fw_version;

	case KGD_ENGINE_SDMA1:
		return adev->sdma.instance[0].fw_version;

	case KGD_ENGINE_SDMA2:
		return adev->sdma.instance[1].fw_version;

	default:
		return 0;
	}

	return 0;
}