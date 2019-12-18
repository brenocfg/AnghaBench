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
 int intel_uc_fw_is_supported (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline bool intel_huc_is_supported(struct intel_huc *huc)
{
	return intel_uc_fw_is_supported(&huc->fw);
}