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
typedef  int /*<<< orphan*/  efi_system_table_t ;
typedef  int /*<<< orphan*/  efi_status_t ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_ARM_LPAE ; 
 int /*<<< orphan*/  CPUID_EXT_MMFR0 ; 
 int /*<<< orphan*/  EFI_SUCCESS ; 
 int /*<<< orphan*/  EFI_UNSUPPORTED ; 
 int /*<<< orphan*/  IS_ENABLED (int /*<<< orphan*/ ) ; 
 int cpuid_feature_extract (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_efi_err (int /*<<< orphan*/ *,char*) ; 

efi_status_t check_platform_features(efi_system_table_t *sys_table_arg)
{
	int block;

	/* non-LPAE kernels can run anywhere */
	if (!IS_ENABLED(CONFIG_ARM_LPAE))
		return EFI_SUCCESS;

	/* LPAE kernels need compatible hardware */
	block = cpuid_feature_extract(CPUID_EXT_MMFR0, 0);
	if (block < 5) {
		pr_efi_err(sys_table_arg, "This LPAE kernel is not supported by your CPU\n");
		return EFI_UNSUPPORTED;
	}
	return EFI_SUCCESS;
}