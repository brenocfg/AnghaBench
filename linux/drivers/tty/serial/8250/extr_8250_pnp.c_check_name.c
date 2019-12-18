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
 char** modem_names ; 
 scalar_t__ strstr (char const*,char const*) ; 

__attribute__((used)) static bool check_name(const char *name)
{
	const char **tmp;

	for (tmp = modem_names; *tmp; tmp++)
		if (strstr(name, *tmp))
			return true;

	return false;
}