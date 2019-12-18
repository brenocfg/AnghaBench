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
typedef  int /*<<< orphan*/  u32 ;
struct intel_uc_fw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __intel_uc_fw_get_upload_size (struct intel_uc_fw*) ; 
 int /*<<< orphan*/  intel_uc_fw_is_available (struct intel_uc_fw*) ; 

__attribute__((used)) static inline u32 intel_uc_fw_get_upload_size(struct intel_uc_fw *uc_fw)
{
	if (!intel_uc_fw_is_available(uc_fw))
		return 0;

	return __intel_uc_fw_get_upload_size(uc_fw);
}