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
typedef  int uint32_t ;
struct TYPE_2__ {scalar_t__ real_vram_size; } ;
struct amdgpu_device {TYPE_1__ gmc; } ;

/* Variables and functions */
 int AMDGPU_GEM_DOMAIN_GTT ; 
 int AMDGPU_GEM_DOMAIN_VRAM ; 
 scalar_t__ AMDGPU_SG_THRESHOLD ; 

uint32_t amdgpu_bo_get_preferred_pin_domain(struct amdgpu_device *adev,
					    uint32_t domain)
{
	if (domain == (AMDGPU_GEM_DOMAIN_VRAM | AMDGPU_GEM_DOMAIN_GTT)) {
		domain = AMDGPU_GEM_DOMAIN_VRAM;
		if (adev->gmc.real_vram_size <= AMDGPU_SG_THRESHOLD)
			domain = AMDGPU_GEM_DOMAIN_GTT;
	}
	return domain;
}