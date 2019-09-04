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
struct amdgpu_device {int flags; } ;

/* Variables and functions */
 int AMDGPU_VRAM_TYPE_DDR2 ; 
 int AMDGPU_VRAM_TYPE_DDR3 ; 
 int AMDGPU_VRAM_TYPE_DDR4 ; 
 int AMDGPU_VRAM_TYPE_GDDR5 ; 
 int AMDGPU_VRAM_TYPE_HBM ; 
 int AMDGPU_VRAM_TYPE_UNKNOWN ; 
 int AMD_IS_APU ; 
#define  ATOM_DGPU_VRAM_TYPE_GDDR5 135 
#define  ATOM_DGPU_VRAM_TYPE_HBM 134 
#define  Ddr2MemType 133 
#define  Ddr3MemType 132 
#define  Ddr4MemType 131 
#define  LpDdr2MemType 130 
#define  LpDdr3MemType 129 
#define  LpDdr4MemType 128 

__attribute__((used)) static int convert_atom_mem_type_to_vram_type (struct amdgpu_device *adev,
					       int atom_mem_type)
{
	int vram_type;

	if (adev->flags & AMD_IS_APU) {
		switch (atom_mem_type) {
		case Ddr2MemType:
		case LpDdr2MemType:
			vram_type = AMDGPU_VRAM_TYPE_DDR2;
			break;
		case Ddr3MemType:
		case LpDdr3MemType:
			vram_type = AMDGPU_VRAM_TYPE_DDR3;
			break;
		case Ddr4MemType:
		case LpDdr4MemType:
			vram_type = AMDGPU_VRAM_TYPE_DDR4;
			break;
		default:
			vram_type = AMDGPU_VRAM_TYPE_UNKNOWN;
			break;
		}
	} else {
		switch (atom_mem_type) {
		case ATOM_DGPU_VRAM_TYPE_GDDR5:
			vram_type = AMDGPU_VRAM_TYPE_GDDR5;
			break;
		case ATOM_DGPU_VRAM_TYPE_HBM:
			vram_type = AMDGPU_VRAM_TYPE_HBM;
			break;
		default:
			vram_type = AMDGPU_VRAM_TYPE_UNKNOWN;
			break;
		}
	}

	return vram_type;
}