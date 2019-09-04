#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  char u8 ;
typedef  char u16 ;
typedef  int /*<<< orphan*/  efi_system_table_t ;
typedef  scalar_t__ efi_status_t ;
struct TYPE_3__ {int load_options_size; char* load_options; } ;
typedef  TYPE_1__ efi_loaded_image_t ;

/* Variables and functions */
 scalar_t__ EFI_SUCCESS ; 
 int /*<<< orphan*/  MAX_CMDLINE_ADDRESS ; 
 scalar_t__ efi_high_alloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,unsigned long*,int /*<<< orphan*/ ) ; 
 char* efi_utf16_to_utf8 (char*,char const*,int) ; 
 scalar_t__ efi_utf8_bytes (int /*<<< orphan*/ ) ; 

char *efi_convert_cmdline(efi_system_table_t *sys_table_arg,
			  efi_loaded_image_t *image,
			  int *cmd_line_len)
{
	const u16 *s2;
	u8 *s1 = NULL;
	unsigned long cmdline_addr = 0;
	int load_options_chars = image->load_options_size / 2; /* UTF-16 */
	const u16 *options = image->load_options;
	int options_bytes = 0;  /* UTF-8 bytes */
	int options_chars = 0;  /* UTF-16 chars */
	efi_status_t status;
	u16 zero = 0;

	if (options) {
		s2 = options;
		while (*s2 && *s2 != '\n'
		       && options_chars < load_options_chars) {
			options_bytes += efi_utf8_bytes(*s2++);
			options_chars++;
		}
	}

	if (!options_chars) {
		/* No command line options, so return empty string*/
		options = &zero;
	}

	options_bytes++;	/* NUL termination */

	status = efi_high_alloc(sys_table_arg, options_bytes, 0,
				&cmdline_addr, MAX_CMDLINE_ADDRESS);
	if (status != EFI_SUCCESS)
		return NULL;

	s1 = (u8 *)cmdline_addr;
	s2 = (const u16 *)options;

	s1 = efi_utf16_to_utf8(s1, s2, options_chars);
	*s1 = '\0';

	*cmd_line_len = options_bytes;
	return (char *)cmdline_addr;
}