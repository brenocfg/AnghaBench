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
struct screen_info {int dummy; } ;
typedef  int /*<<< orphan*/  efi_system_table_t ;
typedef  scalar_t__ efi_status_t ;
typedef  int /*<<< orphan*/  efi_guid_t ;

/* Variables and functions */
 scalar_t__ EFI_BUFFER_TOO_SMALL ; 
 int /*<<< orphan*/  EFI_GRAPHICS_OUTPUT_PROTOCOL_GUID ; 
 int /*<<< orphan*/  EFI_LOCATE_BY_PROTOCOL ; 
 struct screen_info* alloc_screen_info (int /*<<< orphan*/ *) ; 
 scalar_t__ efi_call_early (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned long*,void**) ; 
 int /*<<< orphan*/  efi_setup_gop (int /*<<< orphan*/ *,struct screen_info*,int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  locate_handle ; 

__attribute__((used)) static struct screen_info *setup_graphics(efi_system_table_t *sys_table_arg)
{
	efi_guid_t gop_proto = EFI_GRAPHICS_OUTPUT_PROTOCOL_GUID;
	efi_status_t status;
	unsigned long size;
	void **gop_handle = NULL;
	struct screen_info *si = NULL;

	size = 0;
	status = efi_call_early(locate_handle, EFI_LOCATE_BY_PROTOCOL,
				&gop_proto, NULL, &size, gop_handle);
	if (status == EFI_BUFFER_TOO_SMALL) {
		si = alloc_screen_info(sys_table_arg);
		if (!si)
			return NULL;
		efi_setup_gop(sys_table_arg, si, &gop_proto, size);
	}
	return si;
}