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
struct hid_field {int unit_exponent; int logical_maximum; int logical_minimum; int physical_maximum; int physical_minimum; int unit; } ;
typedef  int __u16 ;
typedef  int __s32 ;

/* Variables and functions */
#define  ABS_MT_POSITION_X 142 
#define  ABS_MT_POSITION_Y 141 
#define  ABS_MT_TOOL_X 140 
#define  ABS_MT_TOOL_Y 139 
#define  ABS_MT_TOUCH_MAJOR 138 
#define  ABS_MT_TOUCH_MINOR 137 
#define  ABS_RX 136 
#define  ABS_RY 135 
#define  ABS_RZ 134 
#define  ABS_TILT_X 133 
#define  ABS_TILT_Y 132 
#define  ABS_WHEEL 131 
#define  ABS_X 130 
#define  ABS_Y 129 
#define  ABS_Z 128 
 int DIV_ROUND_CLOSEST (int,int) ; 

__s32 hidinput_calc_abs_res(const struct hid_field *field, __u16 code)
{
	__s32 unit_exponent = field->unit_exponent;
	__s32 logical_extents = field->logical_maximum -
					field->logical_minimum;
	__s32 physical_extents = field->physical_maximum -
					field->physical_minimum;
	__s32 prev;

	/* Check if the extents are sane */
	if (logical_extents <= 0 || physical_extents <= 0)
		return 0;

	/*
	 * Verify and convert units.
	 * See HID specification v1.11 6.2.2.7 Global Items for unit decoding
	 */
	switch (code) {
	case ABS_X:
	case ABS_Y:
	case ABS_Z:
	case ABS_MT_POSITION_X:
	case ABS_MT_POSITION_Y:
	case ABS_MT_TOOL_X:
	case ABS_MT_TOOL_Y:
	case ABS_MT_TOUCH_MAJOR:
	case ABS_MT_TOUCH_MINOR:
		if (field->unit == 0x11) {		/* If centimeters */
			/* Convert to millimeters */
			unit_exponent += 1;
		} else if (field->unit == 0x13) {	/* If inches */
			/* Convert to millimeters */
			prev = physical_extents;
			physical_extents *= 254;
			if (physical_extents < prev)
				return 0;
			unit_exponent -= 1;
		} else {
			return 0;
		}
		break;

	case ABS_RX:
	case ABS_RY:
	case ABS_RZ:
	case ABS_WHEEL:
	case ABS_TILT_X:
	case ABS_TILT_Y:
		if (field->unit == 0x14) {		/* If degrees */
			/* Convert to radians */
			prev = logical_extents;
			logical_extents *= 573;
			if (logical_extents < prev)
				return 0;
			unit_exponent += 1;
		} else if (field->unit != 0x12) {	/* If not radians */
			return 0;
		}
		break;

	default:
		return 0;
	}

	/* Apply negative unit exponent */
	for (; unit_exponent < 0; unit_exponent++) {
		prev = logical_extents;
		logical_extents *= 10;
		if (logical_extents < prev)
			return 0;
	}
	/* Apply positive unit exponent */
	for (; unit_exponent > 0; unit_exponent--) {
		prev = physical_extents;
		physical_extents *= 10;
		if (physical_extents < prev)
			return 0;
	}

	/* Calculate resolution */
	return DIV_ROUND_CLOSEST(logical_extents, physical_extents);
}