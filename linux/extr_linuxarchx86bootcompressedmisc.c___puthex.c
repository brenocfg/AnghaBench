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
typedef  int /*<<< orphan*/  value ;

/* Variables and functions */
 int /*<<< orphan*/  __putstr (char*) ; 

void __puthex(unsigned long value)
{
	char alpha[2] = "0";
	int bits;

	for (bits = sizeof(value) * 8 - 4; bits >= 0; bits -= 4) {
		unsigned long digit = (value >> bits) & 0xf;

		if (digit < 0xA)
			alpha[0] = '0' + digit;
		else
			alpha[0] = 'a' + (digit - 0xA);

		__putstr(alpha);
	}
}