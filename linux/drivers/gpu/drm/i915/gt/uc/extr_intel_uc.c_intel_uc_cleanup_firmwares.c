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
struct TYPE_4__ {int /*<<< orphan*/  fw; } ;
struct TYPE_3__ {int /*<<< orphan*/  fw; } ;
struct intel_uc {TYPE_2__ guc; TYPE_1__ huc; } ;

/* Variables and functions */
 int /*<<< orphan*/  intel_uc_fw_cleanup_fetch (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  intel_uc_uses_guc (struct intel_uc*) ; 
 scalar_t__ intel_uc_uses_huc (struct intel_uc*) ; 

void intel_uc_cleanup_firmwares(struct intel_uc *uc)
{
	if (!intel_uc_uses_guc(uc))
		return;

	if (intel_uc_uses_huc(uc))
		intel_uc_fw_cleanup_fetch(&uc->huc.fw);

	intel_uc_fw_cleanup_fetch(&uc->guc.fw);
}