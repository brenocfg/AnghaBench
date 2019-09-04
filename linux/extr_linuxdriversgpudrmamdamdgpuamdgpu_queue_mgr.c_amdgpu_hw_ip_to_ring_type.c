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
typedef  enum amdgpu_ring_type { ____Placeholder_amdgpu_ring_type } amdgpu_ring_type ;

/* Variables and functions */
#define  AMDGPU_HW_IP_COMPUTE 132 
#define  AMDGPU_HW_IP_DMA 131 
#define  AMDGPU_HW_IP_GFX 130 
#define  AMDGPU_HW_IP_UVD 129 
#define  AMDGPU_HW_IP_VCE 128 
 int AMDGPU_RING_TYPE_COMPUTE ; 
 int AMDGPU_RING_TYPE_GFX ; 
 int AMDGPU_RING_TYPE_SDMA ; 
 int AMDGPU_RING_TYPE_UVD ; 
 int AMDGPU_RING_TYPE_VCE ; 
 int /*<<< orphan*/  DRM_ERROR (char*,int) ; 

__attribute__((used)) static enum amdgpu_ring_type amdgpu_hw_ip_to_ring_type(int hw_ip)
{
	switch (hw_ip) {
	case AMDGPU_HW_IP_GFX:
		return AMDGPU_RING_TYPE_GFX;
	case AMDGPU_HW_IP_COMPUTE:
		return AMDGPU_RING_TYPE_COMPUTE;
	case AMDGPU_HW_IP_DMA:
		return AMDGPU_RING_TYPE_SDMA;
	case AMDGPU_HW_IP_UVD:
		return AMDGPU_RING_TYPE_UVD;
	case AMDGPU_HW_IP_VCE:
		return AMDGPU_RING_TYPE_VCE;
	default:
		DRM_ERROR("Invalid HW IP specified %d\n", hw_ip);
		return -1;
	}
}