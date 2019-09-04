#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
struct amdgpu_gmc {scalar_t__ gart_size; scalar_t__ vram_end; scalar_t__ vram_start; scalar_t__ gart_start; scalar_t__ gart_end; } ;
struct TYPE_4__ {scalar_t__ mc_mask; } ;
struct TYPE_3__ {scalar_t__ smu_prv_buffer_size; } ;
struct amdgpu_device {int /*<<< orphan*/  dev; TYPE_2__ gmc; TYPE_1__ pm; } ;

/* Variables and functions */
 scalar_t__ ALIGN (scalar_t__,int) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,int,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 

void amdgpu_device_gart_location(struct amdgpu_device *adev,
				 struct amdgpu_gmc *mc)
{
	u64 size_af, size_bf;

	mc->gart_size += adev->pm.smu_prv_buffer_size;

	size_af = adev->gmc.mc_mask - mc->vram_end;
	size_bf = mc->vram_start;
	if (size_bf > size_af) {
		if (mc->gart_size > size_bf) {
			dev_warn(adev->dev, "limiting GART\n");
			mc->gart_size = size_bf;
		}
		mc->gart_start = 0;
	} else {
		if (mc->gart_size > size_af) {
			dev_warn(adev->dev, "limiting GART\n");
			mc->gart_size = size_af;
		}
		/* VCE doesn't like it when BOs cross a 4GB segment, so align
		 * the GART base on a 4GB boundary as well.
		 */
		mc->gart_start = ALIGN(mc->vram_end + 1, 0x100000000ULL);
	}
	mc->gart_end = mc->gart_start + mc->gart_size - 1;
	dev_info(adev->dev, "GART: %lluM 0x%016llX - 0x%016llX\n",
			mc->gart_size >> 20, mc->gart_start, mc->gart_end);
}