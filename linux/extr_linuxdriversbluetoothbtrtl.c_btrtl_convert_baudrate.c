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
typedef  int u32 ;

/* Variables and functions */

__attribute__((used)) static unsigned int btrtl_convert_baudrate(u32 device_baudrate)
{
	switch (device_baudrate) {
	case 0x0252a00a:
		return 230400;

	case 0x05f75004:
		return 921600;

	case 0x00005004:
		return 1000000;

	case 0x04928002:
	case 0x01128002:
		return 1500000;

	case 0x00005002:
		return 2000000;

	case 0x0000b001:
		return 2500000;

	case 0x04928001:
		return 3000000;

	case 0x052a6001:
		return 3500000;

	case 0x00005001:
		return 4000000;

	case 0x0252c014:
	default:
		return 115200;
	}
}