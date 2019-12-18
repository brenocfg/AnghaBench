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
typedef  enum cgs_ucode_id { ____Placeholder_cgs_ucode_id } cgs_ucode_id ;

/* Variables and functions */
 int CGS_UCODE_ID_CP_CE ; 
 int CGS_UCODE_ID_CP_ME ; 
 int CGS_UCODE_ID_CP_MEC_JT1 ; 
 int CGS_UCODE_ID_CP_MEC_JT2 ; 
 int CGS_UCODE_ID_CP_PFP ; 
 int CGS_UCODE_ID_MAXIMUM ; 
 int CGS_UCODE_ID_RLC_G ; 
 int CGS_UCODE_ID_SDMA0 ; 
 int CGS_UCODE_ID_SDMA1 ; 
#define  UCODE_ID_CP_CE 135 
#define  UCODE_ID_CP_ME 134 
#define  UCODE_ID_CP_MEC_JT1 133 
#define  UCODE_ID_CP_MEC_JT2 132 
#define  UCODE_ID_CP_PFP 131 
#define  UCODE_ID_RLC_G 130 
#define  UCODE_ID_SDMA0 129 
#define  UCODE_ID_SDMA1 128 

__attribute__((used)) static enum cgs_ucode_id smu8_convert_fw_type_to_cgs(uint32_t fw_type)
{
	enum cgs_ucode_id result = CGS_UCODE_ID_MAXIMUM;

	switch (fw_type) {
	case UCODE_ID_SDMA0:
		result = CGS_UCODE_ID_SDMA0;
		break;
	case UCODE_ID_SDMA1:
		result = CGS_UCODE_ID_SDMA1;
		break;
	case UCODE_ID_CP_CE:
		result = CGS_UCODE_ID_CP_CE;
		break;
	case UCODE_ID_CP_PFP:
		result = CGS_UCODE_ID_CP_PFP;
		break;
	case UCODE_ID_CP_ME:
		result = CGS_UCODE_ID_CP_ME;
		break;
	case UCODE_ID_CP_MEC_JT1:
		result = CGS_UCODE_ID_CP_MEC_JT1;
		break;
	case UCODE_ID_CP_MEC_JT2:
		result = CGS_UCODE_ID_CP_MEC_JT2;
		break;
	case UCODE_ID_RLC_G:
		result = CGS_UCODE_ID_RLC_G;
		break;
	default:
		break;
	}

	return result;
}