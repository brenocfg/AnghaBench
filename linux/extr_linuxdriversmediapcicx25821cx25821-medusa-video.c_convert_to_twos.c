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
 int abs (long) ; 

__attribute__((used)) static unsigned long convert_to_twos(long numeric, unsigned long bits_len)
{
	unsigned char temp;

	if (numeric >= 0)
		return numeric;
	else {
		temp = ~(abs(numeric) & 0xFF);
		temp += 1;
		return temp;
	}
}