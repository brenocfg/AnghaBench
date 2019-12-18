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
struct intel_uncore {int dummy; } ;
struct intel_guc {int /*<<< orphan*/  fw; } ;
struct intel_gt {struct intel_uncore* uncore; } ;

/* Variables and functions */
 int /*<<< orphan*/  INTEL_UC_FIRMWARE_FAIL ; 
 int /*<<< orphan*/  INTEL_UC_FIRMWARE_RUNNING ; 
 int /*<<< orphan*/  UOS_MOVE ; 
 int /*<<< orphan*/  guc_prepare_xfer (struct intel_uncore*) ; 
 struct intel_gt* guc_to_gt (struct intel_guc*) ; 
 int guc_wait_ucode (struct intel_uncore*) ; 
 int /*<<< orphan*/  guc_xfer_rsa (int /*<<< orphan*/ *,struct intel_uncore*) ; 
 int /*<<< orphan*/  intel_uc_fw_change_status (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int intel_uc_fw_upload (int /*<<< orphan*/ *,struct intel_gt*,int,int /*<<< orphan*/ ) ; 

int intel_guc_fw_upload(struct intel_guc *guc)
{
	struct intel_gt *gt = guc_to_gt(guc);
	struct intel_uncore *uncore = gt->uncore;
	int ret;

	guc_prepare_xfer(uncore);

	/*
	 * Note that GuC needs the CSS header plus uKernel code to be copied
	 * by the DMA engine in one operation, whereas the RSA signature is
	 * loaded via MMIO.
	 */
	guc_xfer_rsa(&guc->fw, uncore);

	/*
	 * Current uCode expects the code to be loaded at 8k; locations below
	 * this are used for the stack.
	 */
	ret = intel_uc_fw_upload(&guc->fw, gt, 0x2000, UOS_MOVE);
	if (ret)
		goto out;

	ret = guc_wait_ucode(uncore);
	if (ret)
		goto out;

	intel_uc_fw_change_status(&guc->fw, INTEL_UC_FIRMWARE_RUNNING);
	return 0;

out:
	intel_uc_fw_change_status(&guc->fw, INTEL_UC_FIRMWARE_FAIL);
	return ret;
}