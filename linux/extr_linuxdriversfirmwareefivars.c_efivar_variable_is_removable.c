#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  efi_guid_t ;
struct TYPE_2__ {char* name; int /*<<< orphan*/  vendor; } ;

/* Variables and functions */
 scalar_t__ efi_guidcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ variable_matches (char const*,size_t,char*,int*) ; 
 TYPE_1__* variable_validate ; 

bool
efivar_variable_is_removable(efi_guid_t vendor, const char *var_name,
			     size_t len)
{
	int i;
	bool found = false;
	int match = 0;

	/*
	 * Check if our variable is in the validated variables list
	 */
	for (i = 0; variable_validate[i].name[0] != '\0'; i++) {
		if (efi_guidcmp(variable_validate[i].vendor, vendor))
			continue;

		if (variable_matches(var_name, len,
				     variable_validate[i].name, &match)) {
			found = true;
			break;
		}
	}

	/*
	 * If it's in our list, it is removable.
	 */
	return found;
}