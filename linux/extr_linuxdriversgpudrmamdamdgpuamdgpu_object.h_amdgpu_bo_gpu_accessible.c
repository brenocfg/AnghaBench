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
struct TYPE_4__ {int mem_type; } ;
struct TYPE_3__ {TYPE_2__ mem; } ;
struct amdgpu_bo {TYPE_1__ tbo; } ;

/* Variables and functions */
#define  TTM_PL_TT 129 
#define  TTM_PL_VRAM 128 
 int amdgpu_gtt_mgr_has_gart_addr (TYPE_2__*) ; 

__attribute__((used)) static inline bool amdgpu_bo_gpu_accessible(struct amdgpu_bo *bo)
{
	switch (bo->tbo.mem.mem_type) {
	case TTM_PL_TT: return amdgpu_gtt_mgr_has_gart_addr(&bo->tbo.mem);
	case TTM_PL_VRAM: return true;
	default: return false;
	}
}