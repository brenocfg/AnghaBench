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
struct amdgpu_hive_info {int pstate; } ;
struct TYPE_3__ {int /*<<< orphan*/  hive_id; int /*<<< orphan*/  node_id; } ;
struct TYPE_4__ {TYPE_1__ xgmi; } ;
struct amdgpu_device {TYPE_2__ gmc; int /*<<< orphan*/  dev; int /*<<< orphan*/  smu; } ;

/* Variables and functions */
 struct amdgpu_hive_info* amdgpu_get_xgmi_hive (struct amdgpu_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ is_support_sw_smu_xgmi (struct amdgpu_device*) ; 
 int smu_set_xgmi_pstate (int /*<<< orphan*/ *,int) ; 

int amdgpu_xgmi_set_pstate(struct amdgpu_device *adev, int pstate)
{
	int ret = 0;
	struct amdgpu_hive_info *hive = amdgpu_get_xgmi_hive(adev, 0);

	if (!hive)
		return 0;

	if (hive->pstate == pstate)
		return 0;

	dev_dbg(adev->dev, "Set xgmi pstate %d.\n", pstate);

	if (is_support_sw_smu_xgmi(adev))
		ret = smu_set_xgmi_pstate(&adev->smu, pstate);
	if (ret)
		dev_err(adev->dev,
			"XGMI: Set pstate failure on device %llx, hive %llx, ret %d",
			adev->gmc.xgmi.node_id,
			adev->gmc.xgmi.hive_id, ret);

	return ret;
}