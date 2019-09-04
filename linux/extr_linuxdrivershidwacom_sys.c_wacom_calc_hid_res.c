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
struct hid_field {int logical_maximum; int physical_maximum; unsigned int unit; int unit_exponent; } ;

/* Variables and functions */
 int /*<<< orphan*/  ABS_X ; 
 int hidinput_calc_abs_res (struct hid_field*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int wacom_calc_hid_res(int logical_extents, int physical_extents,
			       unsigned unit, int exponent)
{
	struct hid_field field = {
		.logical_maximum = logical_extents,
		.physical_maximum = physical_extents,
		.unit = unit,
		.unit_exponent = exponent,
	};

	return hidinput_calc_abs_res(&field, ABS_X);
}