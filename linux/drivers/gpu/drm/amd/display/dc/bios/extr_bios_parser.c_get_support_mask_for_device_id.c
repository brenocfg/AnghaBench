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
typedef  int /*<<< orphan*/  uint32_t ;
struct device_id {int device_type; int /*<<< orphan*/  enum_id; } ;
typedef  enum dal_device_type { ____Placeholder_dal_device_type } dal_device_type ;

/* Variables and functions */
 int /*<<< orphan*/  ATOM_DEVICE_CRT1_SUPPORT ; 
 int /*<<< orphan*/  ATOM_DEVICE_CRT2_SUPPORT ; 
 int /*<<< orphan*/  ATOM_DEVICE_CV_SUPPORT ; 
 int /*<<< orphan*/  ATOM_DEVICE_DFP1_SUPPORT ; 
 int /*<<< orphan*/  ATOM_DEVICE_DFP2_SUPPORT ; 
 int /*<<< orphan*/  ATOM_DEVICE_DFP3_SUPPORT ; 
 int /*<<< orphan*/  ATOM_DEVICE_DFP4_SUPPORT ; 
 int /*<<< orphan*/  ATOM_DEVICE_DFP5_SUPPORT ; 
 int /*<<< orphan*/  ATOM_DEVICE_DFP6_SUPPORT ; 
 int /*<<< orphan*/  ATOM_DEVICE_LCD1_SUPPORT ; 
 int /*<<< orphan*/  ATOM_DEVICE_LCD2_SUPPORT ; 
 int /*<<< orphan*/  ATOM_DEVICE_TV1_SUPPORT ; 
#define  DEVICE_TYPE_CRT 132 
#define  DEVICE_TYPE_CV 131 
#define  DEVICE_TYPE_DFP 130 
#define  DEVICE_TYPE_LCD 129 
#define  DEVICE_TYPE_TV 128 

__attribute__((used)) static uint32_t get_support_mask_for_device_id(struct device_id device_id)
{
	enum dal_device_type device_type = device_id.device_type;
	uint32_t enum_id = device_id.enum_id;

	switch (device_type) {
	case DEVICE_TYPE_LCD:
		switch (enum_id) {
		case 1:
			return ATOM_DEVICE_LCD1_SUPPORT;
		case 2:
			return ATOM_DEVICE_LCD2_SUPPORT;
		default:
			break;
		}
		break;
	case DEVICE_TYPE_CRT:
		switch (enum_id) {
		case 1:
			return ATOM_DEVICE_CRT1_SUPPORT;
		case 2:
			return ATOM_DEVICE_CRT2_SUPPORT;
		default:
			break;
		}
		break;
	case DEVICE_TYPE_DFP:
		switch (enum_id) {
		case 1:
			return ATOM_DEVICE_DFP1_SUPPORT;
		case 2:
			return ATOM_DEVICE_DFP2_SUPPORT;
		case 3:
			return ATOM_DEVICE_DFP3_SUPPORT;
		case 4:
			return ATOM_DEVICE_DFP4_SUPPORT;
		case 5:
			return ATOM_DEVICE_DFP5_SUPPORT;
		case 6:
			return ATOM_DEVICE_DFP6_SUPPORT;
		default:
			break;
		}
		break;
	case DEVICE_TYPE_CV:
		switch (enum_id) {
		case 1:
			return ATOM_DEVICE_CV_SUPPORT;
		default:
			break;
		}
		break;
	case DEVICE_TYPE_TV:
		switch (enum_id) {
		case 1:
			return ATOM_DEVICE_TV1_SUPPORT;
		default:
			break;
		}
		break;
	default:
		break;
	};

	/* Unidentified device ID, return empty support mask. */
	return 0;
}