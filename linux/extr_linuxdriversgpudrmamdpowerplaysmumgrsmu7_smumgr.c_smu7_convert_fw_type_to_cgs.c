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
 int CGS_UCODE_ID_CP_MEC ; 
 int CGS_UCODE_ID_CP_MEC_JT1 ; 
 int CGS_UCODE_ID_CP_MEC_JT2 ; 
 int CGS_UCODE_ID_CP_PFP ; 
 int CGS_UCODE_ID_MAXIMUM ; 
 int CGS_UCODE_ID_RLC_G ; 
 int CGS_UCODE_ID_SDMA0 ; 
 int CGS_UCODE_ID_SDMA1 ; 
 int CGS_UCODE_ID_SMU ; 
 int CGS_UCODE_ID_SMU_SK ; 
 int CGS_UCODE_ID_STORAGE ; 
#define  UCODE_ID_CP_CE 139 
#define  UCODE_ID_CP_ME 138 
#define  UCODE_ID_CP_MEC 137 
#define  UCODE_ID_CP_MEC_JT1 136 
#define  UCODE_ID_CP_MEC_JT2 135 
#define  UCODE_ID_CP_PFP 134 
#define  UCODE_ID_MEC_STORAGE 133 
#define  UCODE_ID_RLC_G 132 
#define  UCODE_ID_SDMA0 131 
#define  UCODE_ID_SDMA1 130 
#define  UCODE_ID_SMU 129 
#define  UCODE_ID_SMU_SK 128 

enum cgs_ucode_id smu7_convert_fw_type_to_cgs(uint32_t fw_type)
{
	enum cgs_ucode_id result = CGS_UCODE_ID_MAXIMUM;

	switch (fw_type) {
	case UCODE_ID_SMU:
		result = CGS_UCODE_ID_SMU;
		break;
	case UCODE_ID_SMU_SK:
		result = CGS_UCODE_ID_SMU_SK;
		break;
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
	case UCODE_ID_CP_MEC:
		result = CGS_UCODE_ID_CP_MEC;
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
	case UCODE_ID_MEC_STORAGE:
		result = CGS_UCODE_ID_STORAGE;
		break;
	default:
		break;
	}

	return result;
}