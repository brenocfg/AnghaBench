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
 int kstrtoint (char const*,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ strncmp (char const*,char*,int) ; 

int srp_parse_tmo(int *tmo, const char *buf)
{
	int res = 0;

	if (strncmp(buf, "off", 3) != 0)
		res = kstrtoint(buf, 0, tmo);
	else
		*tmo = -1;

	return res;
}