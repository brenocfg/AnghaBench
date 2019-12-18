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
struct smu_context {int dummy; } ;

/* Variables and functions */
#define  AMD_IP_BLOCK_TYPE_GFX 131 
#define  AMD_IP_BLOCK_TYPE_SDMA 130 
#define  AMD_IP_BLOCK_TYPE_UVD 129 
#define  AMD_IP_BLOCK_TYPE_VCE 128 
 int smu_dpm_set_uvd_enable (struct smu_context*,int) ; 
 int smu_dpm_set_vce_enable (struct smu_context*,int) ; 
 int smu_gfx_off_control (struct smu_context*,int) ; 
 int smu_powergate_sdma (struct smu_context*,int) ; 

int smu_dpm_set_power_gate(struct smu_context *smu, uint32_t block_type,
			   bool gate)
{
	int ret = 0;

	switch (block_type) {
	case AMD_IP_BLOCK_TYPE_UVD:
		ret = smu_dpm_set_uvd_enable(smu, gate);
		break;
	case AMD_IP_BLOCK_TYPE_VCE:
		ret = smu_dpm_set_vce_enable(smu, gate);
		break;
	case AMD_IP_BLOCK_TYPE_GFX:
		ret = smu_gfx_off_control(smu, gate);
		break;
	case AMD_IP_BLOCK_TYPE_SDMA:
		ret = smu_powergate_sdma(smu, gate);
		break;
	default:
		break;
	}

	return ret;
}