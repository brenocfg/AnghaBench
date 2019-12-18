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
 int /*<<< orphan*/  intel_huc_rsa_data_destroy (struct intel_huc*) ; 
 int /*<<< orphan*/  intel_uc_fw_fini (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  intel_uc_fw_is_available (int /*<<< orphan*/ *) ; 

void intel_huc_fini(struct intel_huc *huc)
{
	if (!intel_uc_fw_is_available(&huc->fw))
		return;

	intel_huc_rsa_data_destroy(huc);
	intel_uc_fw_fini(&huc->fw);
}