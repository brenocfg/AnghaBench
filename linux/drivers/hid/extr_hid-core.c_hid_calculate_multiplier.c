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
struct hid_field {int* value; int logical_minimum; int logical_maximum; int physical_minimum; int physical_maximum; scalar_t__ unit_exponent; } ;
struct hid_device {int dummy; } ;
typedef  int __s32 ;

/* Variables and functions */
 int /*<<< orphan*/  hid_warn (struct hid_device*,char*,int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int hid_calculate_multiplier(struct hid_device *hid,
				     struct hid_field *multiplier)
{
	int m;
	__s32 v = *multiplier->value;
	__s32 lmin = multiplier->logical_minimum;
	__s32 lmax = multiplier->logical_maximum;
	__s32 pmin = multiplier->physical_minimum;
	__s32 pmax = multiplier->physical_maximum;

	/*
	 * "Because OS implementations will generally divide the control's
	 * reported count by the Effective Resolution Multiplier, designers
	 * should take care not to establish a potential Effective
	 * Resolution Multiplier of zero."
	 * HID Usage Table, v1.12, Section 4.3.1, p31
	 */
	if (lmax - lmin == 0)
		return 1;
	/*
	 * Handling the unit exponent is left as an exercise to whoever
	 * finds a device where that exponent is not 0.
	 */
	m = ((v - lmin)/(lmax - lmin) * (pmax - pmin) + pmin);
	if (unlikely(multiplier->unit_exponent != 0)) {
		hid_warn(hid,
			 "unsupported Resolution Multiplier unit exponent %d\n",
			 multiplier->unit_exponent);
	}

	/* There are no devices with an effective multiplier > 255 */
	if (unlikely(m == 0 || m > 255 || m < -255)) {
		hid_warn(hid, "unsupported Resolution Multiplier %d\n", m);
		m = 1;
	}

	return m;
}