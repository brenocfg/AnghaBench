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
typedef  int uint32_t ;

/* Variables and functions */
#define  AMD_IP_BLOCK_TYPE_ACP 134 
#define  AMD_IP_BLOCK_TYPE_GFX 133 
#define  AMD_IP_BLOCK_TYPE_GMC 132 
#define  AMD_IP_BLOCK_TYPE_SDMA 131 
#define  AMD_IP_BLOCK_TYPE_UVD 130 
#define  AMD_IP_BLOCK_TYPE_VCE 129 
#define  AMD_IP_BLOCK_TYPE_VCN 128 
 int /*<<< orphan*/  pp_dpm_powergate_acp (void*,int) ; 
 int pp_dpm_powergate_gfx (void*,int) ; 
 int /*<<< orphan*/  pp_dpm_powergate_mmhub (void*) ; 
 int /*<<< orphan*/  pp_dpm_powergate_sdma (void*,int) ; 
 int /*<<< orphan*/  pp_dpm_powergate_uvd (void*,int) ; 
 int /*<<< orphan*/  pp_dpm_powergate_vce (void*,int) ; 

__attribute__((used)) static int pp_set_powergating_by_smu(void *handle,
				uint32_t block_type, bool gate)
{
	int ret = 0;

	switch (block_type) {
	case AMD_IP_BLOCK_TYPE_UVD:
	case AMD_IP_BLOCK_TYPE_VCN:
		pp_dpm_powergate_uvd(handle, gate);
		break;
	case AMD_IP_BLOCK_TYPE_VCE:
		pp_dpm_powergate_vce(handle, gate);
		break;
	case AMD_IP_BLOCK_TYPE_GMC:
		pp_dpm_powergate_mmhub(handle);
		break;
	case AMD_IP_BLOCK_TYPE_GFX:
		ret = pp_dpm_powergate_gfx(handle, gate);
		break;
	case AMD_IP_BLOCK_TYPE_ACP:
		pp_dpm_powergate_acp(handle, gate);
		break;
	case AMD_IP_BLOCK_TYPE_SDMA:
		pp_dpm_powergate_sdma(handle, gate);
		break;
	default:
		break;
	}
	return ret;
}