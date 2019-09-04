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
 unsigned int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int IS_GENERAL_ERR_START ; 
 int /*<<< orphan*/ * cce_misc_names ; 
 int /*<<< orphan*/  snprintf (char*,size_t,char*,int) ; 
 int /*<<< orphan*/  strncpy (char*,int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static char *is_misc_err_name(char *buf, size_t bsize, unsigned int source)
{
	if (source < ARRAY_SIZE(cce_misc_names))
		strncpy(buf, cce_misc_names[source], bsize);
	else
		snprintf(buf, bsize, "Reserved%u",
			 source + IS_GENERAL_ERR_START);

	return buf;
}