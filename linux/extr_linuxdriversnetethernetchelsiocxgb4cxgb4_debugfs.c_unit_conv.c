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
 int /*<<< orphan*/  snprintf (char*,size_t,char*,unsigned int,...) ; 

__attribute__((used)) static char *unit_conv(char *buf, size_t len, unsigned int val,
		       unsigned int factor)
{
	unsigned int rem = val % factor;

	if (rem == 0) {
		snprintf(buf, len, "%u", val / factor);
	} else {
		while (rem % 10 == 0)
			rem /= 10;
		snprintf(buf, len, "%u.%u", val / factor, rem);
	}
	return buf;
}