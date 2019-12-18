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

__attribute__((used)) static bool alps_check_valid_firmware_id(unsigned char id[])
{
	if (id[0] == 0x73)
		return true;

	if (id[0] == 0x88 &&
	    (id[1] == 0x07 ||
	     id[1] == 0x08 ||
	     (id[1] & 0xf0) == 0xb0 ||
	     (id[1] & 0xf0) == 0xc0)) {
		return true;
	}

	return false;
}