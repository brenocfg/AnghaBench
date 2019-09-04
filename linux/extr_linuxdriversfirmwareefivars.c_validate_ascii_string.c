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
typedef  int u8 ;
typedef  int /*<<< orphan*/  efi_char16_t ;

/* Variables and functions */

__attribute__((used)) static bool
validate_ascii_string(efi_char16_t *var_name, int match, u8 *buffer,
		      unsigned long len)
{
	int i;

	for (i = 0; i < len; i++) {
		if (buffer[i] > 127)
			return false;

		if (buffer[i] == 0)
			return true;
	}

	return false;
}