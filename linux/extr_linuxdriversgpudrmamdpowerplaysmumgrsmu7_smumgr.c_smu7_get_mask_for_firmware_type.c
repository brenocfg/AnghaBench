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
#define  UCODE_ID_CP_CE 136 
 int UCODE_ID_CP_CE_MASK ; 
#define  UCODE_ID_CP_ME 135 
#define  UCODE_ID_CP_MEC 134 
#define  UCODE_ID_CP_MEC_JT1 133 
#define  UCODE_ID_CP_MEC_JT2 132 
 int UCODE_ID_CP_MEC_MASK ; 
 int UCODE_ID_CP_ME_MASK ; 
#define  UCODE_ID_CP_PFP 131 
 int UCODE_ID_CP_PFP_MASK ; 
#define  UCODE_ID_RLC_G 130 
 int UCODE_ID_RLC_G_MASK ; 
#define  UCODE_ID_SDMA0 129 
 int UCODE_ID_SDMA0_MASK ; 
#define  UCODE_ID_SDMA1 128 
 int UCODE_ID_SDMA1_MASK ; 
 int /*<<< orphan*/  pr_info (char*) ; 

__attribute__((used)) static uint32_t smu7_get_mask_for_firmware_type(uint32_t fw_type)
{
	uint32_t result = 0;

	switch (fw_type) {
	case UCODE_ID_SDMA0:
		result = UCODE_ID_SDMA0_MASK;
		break;
	case UCODE_ID_SDMA1:
		result = UCODE_ID_SDMA1_MASK;
		break;
	case UCODE_ID_CP_CE:
		result = UCODE_ID_CP_CE_MASK;
		break;
	case UCODE_ID_CP_PFP:
		result = UCODE_ID_CP_PFP_MASK;
		break;
	case UCODE_ID_CP_ME:
		result = UCODE_ID_CP_ME_MASK;
		break;
	case UCODE_ID_CP_MEC:
	case UCODE_ID_CP_MEC_JT1:
	case UCODE_ID_CP_MEC_JT2:
		result = UCODE_ID_CP_MEC_MASK;
		break;
	case UCODE_ID_RLC_G:
		result = UCODE_ID_RLC_G_MASK;
		break;
	default:
		pr_info("UCode type is out of range! \n");
		result = 0;
	}

	return result;
}