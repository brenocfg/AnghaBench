#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct smu7_hwmgr {int is_memory_gddr5; } ;
struct pp_hwmgr {struct amdgpu_device* adev; scalar_t__ backend; } ;
struct TYPE_2__ {scalar_t__ vram_type; } ;
struct amdgpu_device {TYPE_1__ gmc; } ;

/* Variables and functions */
 scalar_t__ AMDGPU_VRAM_TYPE_GDDR5 ; 

__attribute__((used)) static int smu7_get_memory_type(struct pp_hwmgr *hwmgr)
{
	struct smu7_hwmgr *data = (struct smu7_hwmgr *)(hwmgr->backend);
	struct amdgpu_device *adev = hwmgr->adev;

	data->is_memory_gddr5 = (adev->gmc.vram_type == AMDGPU_VRAM_TYPE_GDDR5);

	return 0;
}