#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct hid_sensor_hub_attribute_info {scalar_t__ units; int /*<<< orphan*/  unit_expo; } ;
struct TYPE_3__ {scalar_t__ usage_id; scalar_t__ unit; int /*<<< orphan*/  scale_val1; int /*<<< orphan*/  scale_val0; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int IIO_VAL_INT_PLUS_NANO ; 
 int /*<<< orphan*/  adjust_exponent_nano (int*,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int hid_sensor_convert_exponent (int /*<<< orphan*/ ) ; 
 TYPE_1__* unit_conversion ; 

int hid_sensor_format_scale(u32 usage_id,
			struct hid_sensor_hub_attribute_info *attr_info,
			int *val0, int *val1)
{
	int i;
	int exp;

	*val0 = 1;
	*val1 = 0;

	for (i = 0; i < ARRAY_SIZE(unit_conversion); ++i) {
		if (unit_conversion[i].usage_id == usage_id &&
			unit_conversion[i].unit == attr_info->units) {
			exp  = hid_sensor_convert_exponent(
						attr_info->unit_expo);
			adjust_exponent_nano(val0, val1,
					unit_conversion[i].scale_val0,
					unit_conversion[i].scale_val1, exp);
			break;
		}
	}

	return IIO_VAL_INT_PLUS_NANO;
}