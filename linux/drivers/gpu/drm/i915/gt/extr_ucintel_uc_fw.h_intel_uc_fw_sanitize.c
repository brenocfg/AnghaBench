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
struct intel_uc_fw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  INTEL_UC_FIRMWARE_AVAILABLE ; 
 int /*<<< orphan*/  intel_uc_fw_change_status (struct intel_uc_fw*,int /*<<< orphan*/ ) ; 
 scalar_t__ intel_uc_fw_is_loaded (struct intel_uc_fw*) ; 

__attribute__((used)) static inline void intel_uc_fw_sanitize(struct intel_uc_fw *uc_fw)
{
	if (intel_uc_fw_is_loaded(uc_fw))
		intel_uc_fw_change_status(uc_fw, INTEL_UC_FIRMWARE_AVAILABLE);
}