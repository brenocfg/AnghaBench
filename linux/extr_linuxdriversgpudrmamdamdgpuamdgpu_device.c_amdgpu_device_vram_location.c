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
typedef  int uint64_t ;
typedef  scalar_t__ u64 ;
struct amdgpu_gmc {int mc_vram_size; int real_vram_size; scalar_t__ vram_end; scalar_t__ vram_start; } ;
struct amdgpu_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ amdgpu_vram_limit ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,int,scalar_t__,scalar_t__,int) ; 

void amdgpu_device_vram_location(struct amdgpu_device *adev,
				 struct amdgpu_gmc *mc, u64 base)
{
	uint64_t limit = (uint64_t)amdgpu_vram_limit << 20;

	mc->vram_start = base;
	mc->vram_end = mc->vram_start + mc->mc_vram_size - 1;
	if (limit && limit < mc->real_vram_size)
		mc->real_vram_size = limit;
	dev_info(adev->dev, "VRAM: %lluM 0x%016llX - 0x%016llX (%lluM used)\n",
			mc->mc_vram_size >> 20, mc->vram_start,
			mc->vram_end, mc->real_vram_size >> 20);
}