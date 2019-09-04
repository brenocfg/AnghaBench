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
 char tolower (char) ; 

__attribute__((used)) static unsigned char atohx(unsigned char *dst, char *src)
{
	unsigned char value = 0;

	char msb = tolower(*src) - '0';
	char lsb = tolower(*(src + 1)) - '0';

	if (msb > 9)
		msb -= 7;
	if (lsb > 9)
		lsb -= 7;

	*dst = value = ((msb & 0xF) << 4) | (lsb & 0xF);
	return value;
}