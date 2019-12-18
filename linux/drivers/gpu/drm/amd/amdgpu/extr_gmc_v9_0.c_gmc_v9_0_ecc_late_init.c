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
struct ras_fs_if {char* sysfs_name; char* debugfs_name; } ;
struct ras_common_if {char* name; int /*<<< orphan*/  sub_block_index; int /*<<< orphan*/  type; int /*<<< orphan*/  block; } ;

/* Variables and functions */
 int /*<<< orphan*/  AMDGPU_RAS_BLOCK__MMHUB ; 
 int /*<<< orphan*/  AMDGPU_RAS_BLOCK__UMC ; 
 int /*<<< orphan*/  AMDGPU_RAS_ERROR__MULTI_UNCORRECTABLE ; 
 int gmc_v9_0_ecc_ras_block_late_init (void*,struct ras_fs_if*,struct ras_common_if*) ; 

__attribute__((used)) static int gmc_v9_0_ecc_late_init(void *handle)
{
	int r;

	struct ras_fs_if umc_fs_info = {
		.sysfs_name = "umc_err_count",
		.debugfs_name = "umc_err_inject",
	};
	struct ras_common_if umc_ras_block = {
		.block = AMDGPU_RAS_BLOCK__UMC,
		.type = AMDGPU_RAS_ERROR__MULTI_UNCORRECTABLE,
		.sub_block_index = 0,
		.name = "umc",
	};
	struct ras_fs_if mmhub_fs_info = {
		.sysfs_name = "mmhub_err_count",
		.debugfs_name = "mmhub_err_inject",
	};
	struct ras_common_if mmhub_ras_block = {
		.block = AMDGPU_RAS_BLOCK__MMHUB,
		.type = AMDGPU_RAS_ERROR__MULTI_UNCORRECTABLE,
		.sub_block_index = 0,
		.name = "mmhub",
	};

	r = gmc_v9_0_ecc_ras_block_late_init(handle,
			&umc_fs_info, &umc_ras_block);
	if (r)
		return r;

	r = gmc_v9_0_ecc_ras_block_late_init(handle,
			&mmhub_fs_info, &mmhub_ras_block);
	return r;
}