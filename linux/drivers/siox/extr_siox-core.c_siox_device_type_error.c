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
typedef  int u8 ;
struct siox_device {int statustype; } ;

/* Variables and functions */
 int SIOX_STATUS_TYPE ; 

__attribute__((used)) static bool siox_device_type_error(struct siox_device *sdevice, u8 status_clean)
{
	u8 statustype = (status_clean & SIOX_STATUS_TYPE) >> 4;

	/*
	 * If the device knows which value the type bits should have, check
	 * against this value otherwise just rule out the invalid values 0b0000
	 * and 0b1111.
	 */
	if (sdevice->statustype) {
		if (statustype != sdevice->statustype)
			return true;
	} else {
		switch (statustype) {
		case 0:
		case 0xf:
			return true;
		}
	}

	return false;
}