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

/* Variables and functions */
 int AMDGPU_VRAM_TYPE_DDR2 ; 
 int AMDGPU_VRAM_TYPE_DDR3 ; 
 int AMDGPU_VRAM_TYPE_GDDR1 ; 
 int AMDGPU_VRAM_TYPE_GDDR3 ; 
 int AMDGPU_VRAM_TYPE_GDDR4 ; 
 int AMDGPU_VRAM_TYPE_GDDR5 ; 
 int AMDGPU_VRAM_TYPE_HBM ; 
 int AMDGPU_VRAM_TYPE_UNKNOWN ; 
#define  MC_SEQ_MISC0__MT__DDR2 134 
#define  MC_SEQ_MISC0__MT__DDR3 133 
#define  MC_SEQ_MISC0__MT__GDDR1 132 
#define  MC_SEQ_MISC0__MT__GDDR3 131 
#define  MC_SEQ_MISC0__MT__GDDR4 130 
#define  MC_SEQ_MISC0__MT__GDDR5 129 
#define  MC_SEQ_MISC0__MT__HBM 128 

__attribute__((used)) static int gmc_v8_0_convert_vram_type(int mc_seq_vram_type)
{
	switch (mc_seq_vram_type) {
	case MC_SEQ_MISC0__MT__GDDR1:
		return AMDGPU_VRAM_TYPE_GDDR1;
	case MC_SEQ_MISC0__MT__DDR2:
		return AMDGPU_VRAM_TYPE_DDR2;
	case MC_SEQ_MISC0__MT__GDDR3:
		return AMDGPU_VRAM_TYPE_GDDR3;
	case MC_SEQ_MISC0__MT__GDDR4:
		return AMDGPU_VRAM_TYPE_GDDR4;
	case MC_SEQ_MISC0__MT__GDDR5:
		return AMDGPU_VRAM_TYPE_GDDR5;
	case MC_SEQ_MISC0__MT__HBM:
		return AMDGPU_VRAM_TYPE_HBM;
	case MC_SEQ_MISC0__MT__DDR3:
		return AMDGPU_VRAM_TYPE_DDR3;
	default:
		return AMDGPU_VRAM_TYPE_UNKNOWN;
	}
}