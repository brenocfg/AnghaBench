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
typedef  int u32 ;

/* Variables and functions */
 int AMDGPU_GEM_DOMAIN_CPU ; 
 int AMDGPU_GEM_DOMAIN_GDS ; 
 int AMDGPU_GEM_DOMAIN_GTT ; 
 int AMDGPU_GEM_DOMAIN_GWS ; 
 int AMDGPU_GEM_DOMAIN_OA ; 
 int AMDGPU_GEM_DOMAIN_VRAM ; 
#define  AMDGPU_PL_GDS 133 
#define  AMDGPU_PL_GWS 132 
#define  AMDGPU_PL_OA 131 
#define  TTM_PL_SYSTEM 130 
#define  TTM_PL_TT 129 
#define  TTM_PL_VRAM 128 

__attribute__((used)) static inline unsigned amdgpu_mem_type_to_domain(u32 mem_type)
{
	switch (mem_type) {
	case TTM_PL_VRAM:
		return AMDGPU_GEM_DOMAIN_VRAM;
	case TTM_PL_TT:
		return AMDGPU_GEM_DOMAIN_GTT;
	case TTM_PL_SYSTEM:
		return AMDGPU_GEM_DOMAIN_CPU;
	case AMDGPU_PL_GDS:
		return AMDGPU_GEM_DOMAIN_GDS;
	case AMDGPU_PL_GWS:
		return AMDGPU_GEM_DOMAIN_GWS;
	case AMDGPU_PL_OA:
		return AMDGPU_GEM_DOMAIN_OA;
	default:
		break;
	}
	return 0;
}