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
typedef  int /*<<< orphan*/  phandle ;

/* Variables and functions */
 int prom_getint (int /*<<< orphan*/ ,char const*) ; 

int prom_getintdefault(phandle node, const char *property, int deflt)
{
	int retval;

	retval = prom_getint(node, property);
	if (retval == -1)
		return deflt;

	return retval;
}