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
#define  DMI_BOARD_VENDOR 130 
#define  DMI_NONE 129 
#define  DMI_SYS_VENDOR 128 
 scalar_t__* dmi_ident ; 
 scalar_t__ strstr (scalar_t__,char const*) ; 

int dmi_name_in_vendors(const char *str)
{
	static int fields[] = { DMI_SYS_VENDOR, DMI_BOARD_VENDOR, DMI_NONE };
	int i;
	for (i = 0; fields[i] != DMI_NONE; i++) {
		int f = fields[i];
		if (dmi_ident[f] && strstr(dmi_ident[f], str))
			return 1;
	}
	return 0;
}