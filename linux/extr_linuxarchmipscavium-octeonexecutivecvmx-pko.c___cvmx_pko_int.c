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

/* Variables and functions */

__attribute__((used)) static int __cvmx_pko_int(int interface, int index)
{
	switch (interface) {
	case 0:
		return index;
	case 1:
		return 4;
	case 2:
		return index + 0x08;
	case 3:
		return index + 0x0c;
	case 4:
		return index + 0x10;
	case 5:
		return 0x1c;
	case 6:
		return 0x1d;
	case 7:
		return 0x1e;
	case 8:
		return 0x1f;
	default:
		return -1;
	}
}