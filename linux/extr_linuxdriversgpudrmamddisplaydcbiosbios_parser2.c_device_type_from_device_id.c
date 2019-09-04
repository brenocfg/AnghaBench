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
typedef  int uint16_t ;
struct device_id {int raw_device_tag; int enum_id; void* device_type; } ;

/* Variables and functions */
#define  ATOM_DISPLAY_DFP1_SUPPORT 134 
#define  ATOM_DISPLAY_DFP2_SUPPORT 133 
#define  ATOM_DISPLAY_DFP3_SUPPORT 132 
#define  ATOM_DISPLAY_DFP4_SUPPORT 131 
#define  ATOM_DISPLAY_DFP5_SUPPORT 130 
#define  ATOM_DISPLAY_DFP6_SUPPORT 129 
#define  ATOM_DISPLAY_LCD1_SUPPORT 128 
 int /*<<< orphan*/  BREAK_TO_DEBUGGER () ; 
 void* DEVICE_TYPE_DFP ; 
 void* DEVICE_TYPE_LCD ; 
 void* DEVICE_TYPE_UNKNOWN ; 

__attribute__((used)) static struct device_id device_type_from_device_id(uint16_t device_id)
{

	struct device_id result_device_id;

	result_device_id.raw_device_tag = device_id;

	switch (device_id) {
	case ATOM_DISPLAY_LCD1_SUPPORT:
		result_device_id.device_type = DEVICE_TYPE_LCD;
		result_device_id.enum_id = 1;
		break;

	case ATOM_DISPLAY_DFP1_SUPPORT:
		result_device_id.device_type = DEVICE_TYPE_DFP;
		result_device_id.enum_id = 1;
		break;

	case ATOM_DISPLAY_DFP2_SUPPORT:
		result_device_id.device_type = DEVICE_TYPE_DFP;
		result_device_id.enum_id = 2;
		break;

	case ATOM_DISPLAY_DFP3_SUPPORT:
		result_device_id.device_type = DEVICE_TYPE_DFP;
		result_device_id.enum_id = 3;
		break;

	case ATOM_DISPLAY_DFP4_SUPPORT:
		result_device_id.device_type = DEVICE_TYPE_DFP;
		result_device_id.enum_id = 4;
		break;

	case ATOM_DISPLAY_DFP5_SUPPORT:
		result_device_id.device_type = DEVICE_TYPE_DFP;
		result_device_id.enum_id = 5;
		break;

	case ATOM_DISPLAY_DFP6_SUPPORT:
		result_device_id.device_type = DEVICE_TYPE_DFP;
		result_device_id.enum_id = 6;
		break;

	default:
		BREAK_TO_DEBUGGER(); /* Invalid device Id */
		result_device_id.device_type = DEVICE_TYPE_UNKNOWN;
		result_device_id.enum_id = 0;
	}
	return result_device_id;
}