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
typedef  scalar_t__ u32 ;
struct device {int dummy; } ;
struct TYPE_5__ {TYPE_3__* acp_cell; TYPE_3__* acp_genpd; TYPE_3__* acp_res; int /*<<< orphan*/  parent; int /*<<< orphan*/  cgs_device; } ;
struct amdgpu_device {TYPE_2__ acp; TYPE_1__* pdev; } ;
struct TYPE_6__ {int /*<<< orphan*/  name; } ;
struct TYPE_4__ {struct device dev; } ;

/* Variables and functions */
 scalar_t__ ACP_CLOCK_EN_TIME_OUT_VALUE ; 
 scalar_t__ ACP_CONTROL__ClkEn_MASK ; 
 int ACP_DEVS ; 
 scalar_t__ ACP_SOFT_RESET_DONE_TIME_OUT_VALUE ; 
 scalar_t__ ACP_SOFT_RESET__SoftResetAudDone_MASK ; 
 scalar_t__ ACP_SOFT_RESET__SoftResetAud_MASK ; 
 int /*<<< orphan*/  AMD_IP_BLOCK_TYPE_ACP ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  amdgpu_dpm_set_powergating_by_smu (struct amdgpu_device*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ cgs_read_register (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cgs_write_register (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 struct device* get_mfd_cell_dev (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  kfree (TYPE_3__*) ; 
 int /*<<< orphan*/  mfd_remove_devices (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmACP_CONTROL ; 
 int /*<<< orphan*/  mmACP_SOFT_RESET ; 
 int /*<<< orphan*/  mmACP_STATUS ; 
 int pm_genpd_remove_device (struct device*) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int acp_hw_fini(void *handle)
{
	int i, ret;
	u32 val = 0;
	u32 count = 0;
	struct device *dev;
	struct amdgpu_device *adev = (struct amdgpu_device *)handle;

	/* return early if no ACP */
	if (!adev->acp.acp_genpd) {
		amdgpu_dpm_set_powergating_by_smu(adev, AMD_IP_BLOCK_TYPE_ACP, false);
		return 0;
	}

	/* Assert Soft reset of ACP */
	val = cgs_read_register(adev->acp.cgs_device, mmACP_SOFT_RESET);

	val |= ACP_SOFT_RESET__SoftResetAud_MASK;
	cgs_write_register(adev->acp.cgs_device, mmACP_SOFT_RESET, val);

	count = ACP_SOFT_RESET_DONE_TIME_OUT_VALUE;
	while (true) {
		val = cgs_read_register(adev->acp.cgs_device, mmACP_SOFT_RESET);
		if (ACP_SOFT_RESET__SoftResetAudDone_MASK ==
		    (val & ACP_SOFT_RESET__SoftResetAudDone_MASK))
			break;
		if (--count == 0) {
			dev_err(&adev->pdev->dev, "Failed to reset ACP\n");
			return -ETIMEDOUT;
		}
		udelay(100);
	}
	/* Disable ACP clock */
	val = cgs_read_register(adev->acp.cgs_device, mmACP_CONTROL);
	val &= ~ACP_CONTROL__ClkEn_MASK;
	cgs_write_register(adev->acp.cgs_device, mmACP_CONTROL, val);

	count = ACP_CLOCK_EN_TIME_OUT_VALUE;

	while (true) {
		val = cgs_read_register(adev->acp.cgs_device, mmACP_STATUS);
		if (val & (u32) 0x1)
			break;
		if (--count == 0) {
			dev_err(&adev->pdev->dev, "Failed to reset ACP\n");
			return -ETIMEDOUT;
		}
		udelay(100);
	}

	for (i = 0; i < ACP_DEVS ; i++) {
		dev = get_mfd_cell_dev(adev->acp.acp_cell[i].name, i);
		ret = pm_genpd_remove_device(dev);
		/* If removal fails, dont giveup and try rest */
		if (ret)
			dev_err(dev, "remove dev from genpd failed\n");
	}

	mfd_remove_devices(adev->acp.parent);
	kfree(adev->acp.acp_res);
	kfree(adev->acp.acp_genpd);
	kfree(adev->acp.acp_cell);

	return 0;
}