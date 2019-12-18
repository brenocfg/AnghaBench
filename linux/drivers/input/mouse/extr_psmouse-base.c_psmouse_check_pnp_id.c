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
 int /*<<< orphan*/  strcasecmp (char const*,char const* const) ; 

__attribute__((used)) static bool psmouse_check_pnp_id(const char *id, const char * const ids[])
{
	int i;

	for (i = 0; ids[i]; i++)
		if (!strcasecmp(id, ids[i]))
			return true;

	return false;
}