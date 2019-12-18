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
 int RADEON_GEM_DOMAIN_CPU ; 
 int RADEON_GEM_DOMAIN_GTT ; 
 int RADEON_GEM_DOMAIN_VRAM ; 
#define  TTM_PL_SYSTEM 130 
#define  TTM_PL_TT 129 
#define  TTM_PL_VRAM 128 

__attribute__((used)) static inline unsigned radeon_mem_type_to_domain(u32 mem_type)
{
	switch (mem_type) {
	case TTM_PL_VRAM:
		return RADEON_GEM_DOMAIN_VRAM;
	case TTM_PL_TT:
		return RADEON_GEM_DOMAIN_GTT;
	case TTM_PL_SYSTEM:
		return RADEON_GEM_DOMAIN_CPU;
	default:
		break;
	}
	return 0;
}