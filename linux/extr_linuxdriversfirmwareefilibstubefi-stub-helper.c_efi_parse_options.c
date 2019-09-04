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
typedef  int /*<<< orphan*/  efi_status_t ;

/* Variables and functions */
 int /*<<< orphan*/  EFI_SUCCESS ; 
 unsigned long __chunk_size ; 
 int __nokaslr ; 
 int __novamap ; 
 int __quiet ; 
 int /*<<< orphan*/  strlen (char*) ; 
 int /*<<< orphan*/  strncmp (char*,char*,int) ; 
 char* strstr (char const*,char*) ; 

efi_status_t efi_parse_options(char const *cmdline)
{
	char *str;

	str = strstr(cmdline, "nokaslr");
	if (str == cmdline || (str && str > cmdline && *(str - 1) == ' '))
		__nokaslr = 1;

	str = strstr(cmdline, "quiet");
	if (str == cmdline || (str && str > cmdline && *(str - 1) == ' '))
		__quiet = 1;

	/*
	 * If no EFI parameters were specified on the cmdline we've got
	 * nothing to do.
	 */
	str = strstr(cmdline, "efi=");
	if (!str)
		return EFI_SUCCESS;

	/* Skip ahead to first argument */
	str += strlen("efi=");

	/*
	 * Remember, because efi= is also used by the kernel we need to
	 * skip over arguments we don't understand.
	 */
	while (*str && *str != ' ') {
		if (!strncmp(str, "nochunk", 7)) {
			str += strlen("nochunk");
			__chunk_size = -1UL;
		}

		if (!strncmp(str, "novamap", 7)) {
			str += strlen("novamap");
			__novamap = 1;
		}

		/* Group words together, delimited by "," */
		while (*str && *str != ' ' && *str != ',')
			str++;

		if (*str == ',')
			str++;
	}

	return EFI_SUCCESS;
}