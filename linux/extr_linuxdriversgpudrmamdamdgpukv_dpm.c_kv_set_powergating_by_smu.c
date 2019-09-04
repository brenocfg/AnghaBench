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
#define  AMD_IP_BLOCK_TYPE_UVD 129 
#define  AMD_IP_BLOCK_TYPE_VCE 128 
 int /*<<< orphan*/  kv_dpm_powergate_uvd (void*,int) ; 
 int /*<<< orphan*/  kv_dpm_powergate_vce (void*,int) ; 

__attribute__((used)) static int kv_set_powergating_by_smu(void *handle,
				uint32_t block_type, bool gate)
{
	switch (block_type) {
	case AMD_IP_BLOCK_TYPE_UVD:
		kv_dpm_powergate_uvd(handle, gate);
		break;
	case AMD_IP_BLOCK_TYPE_VCE:
		kv_dpm_powergate_vce(handle, gate);
		break;
	default:
		break;
	}
	return 0;
}