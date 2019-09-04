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
 int ARRAY_SIZE (char**) ; 
 int HGPK_MODE_INVALID ; 
 char** hgpk_mode_names ; 
 int strlen (char const*) ; 
 int /*<<< orphan*/  strncasecmp (char const*,char const*,int) ; 

__attribute__((used)) static int hgpk_mode_from_name(const char *buf, int len)
{
	int i;

	for (i = 0; i < ARRAY_SIZE(hgpk_mode_names); i++) {
		const char *name = hgpk_mode_names[i];
		if (strlen(name) == len && !strncasecmp(name, buf, len))
			return i;
	}

	return HGPK_MODE_INVALID;
}