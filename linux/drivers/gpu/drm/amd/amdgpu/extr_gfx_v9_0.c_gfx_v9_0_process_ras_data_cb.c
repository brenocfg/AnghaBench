#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct ras_err_data {int dummy; } ;
struct amdgpu_iv_entry {int dummy; } ;
struct TYPE_6__ {TYPE_2__* funcs; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct amdgpu_device {TYPE_3__ gfx; TYPE_1__ kfd; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* query_ras_error_count ) (struct amdgpu_device*,struct ras_err_data*) ;} ;

/* Variables and functions */
 int AMDGPU_RAS_SUCCESS ; 
 int /*<<< orphan*/  amdgpu_ras_reset_gpu (struct amdgpu_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kgd2kfd_set_sram_ecc_flag (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct amdgpu_device*,struct ras_err_data*) ; 

__attribute__((used)) static int gfx_v9_0_process_ras_data_cb(struct amdgpu_device *adev,
		struct ras_err_data *err_data,
		struct amdgpu_iv_entry *entry)
{
	/* TODO ue will trigger an interrupt. */
	kgd2kfd_set_sram_ecc_flag(adev->kfd.dev);
	if (adev->gfx.funcs->query_ras_error_count)
		adev->gfx.funcs->query_ras_error_count(adev, err_data);
	amdgpu_ras_reset_gpu(adev, 0);
	return AMDGPU_RAS_SUCCESS;
}