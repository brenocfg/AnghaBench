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
typedef  int /*<<< orphan*/  uint32_t ;
struct ras_err_data {int /*<<< orphan*/  ue_count; int /*<<< orphan*/  ce_count; } ;
struct amdgpu_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  umc_v6_1_querry_uncorrectable_error_count (struct amdgpu_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  umc_v6_1_query_correctable_error_count (struct amdgpu_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void umc_v6_1_query_error_count(struct amdgpu_device *adev,
					   struct ras_err_data *err_data, uint32_t umc_reg_offset,
					   uint32_t channel_index)
{
	umc_v6_1_query_correctable_error_count(adev, umc_reg_offset,
						   &(err_data->ce_count));
	umc_v6_1_querry_uncorrectable_error_count(adev, umc_reg_offset,
						  &(err_data->ue_count));
}