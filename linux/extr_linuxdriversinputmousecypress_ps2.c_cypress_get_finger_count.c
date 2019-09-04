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
 unsigned char ABS_HSCROLL_BIT ; 

__attribute__((used)) static int cypress_get_finger_count(unsigned char header_byte)
{
	unsigned char bits6_7;
	int finger_count;

	bits6_7 = header_byte >> 6;
	finger_count = bits6_7 & 0x03;

	if (finger_count == 1)
		return 1;

	if (header_byte & ABS_HSCROLL_BIT) {
		/* HSCROLL gets added on to 0 finger count. */
		switch (finger_count) {
			case 0:	return 4;
			case 2: return 5;
			default:
				/* Invalid contact (e.g. palm). Ignore it. */
				return 0;
		}
	}

	return finger_count;
}