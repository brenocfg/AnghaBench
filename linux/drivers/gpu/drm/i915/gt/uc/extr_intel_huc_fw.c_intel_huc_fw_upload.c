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
struct intel_huc {int /*<<< orphan*/  fw; } ;

/* Variables and functions */
 int /*<<< orphan*/  HUC_UKERNEL ; 
 int /*<<< orphan*/  huc_to_gt (struct intel_huc*) ; 
 int intel_uc_fw_upload (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int intel_huc_fw_upload(struct intel_huc *huc)
{
	/* HW doesn't look at destination address for HuC, so set it to 0 */
	return intel_uc_fw_upload(&huc->fw, huc_to_gt(huc), 0, HUC_UKERNEL);
}