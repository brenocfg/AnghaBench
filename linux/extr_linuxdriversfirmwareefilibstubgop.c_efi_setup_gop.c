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
 int /*<<< orphan*/  EFI_LOADER_DATA ; 
 int /*<<< orphan*/  EFI_LOCATE_BY_PROTOCOL ; 
 scalar_t__ EFI_SUCCESS ; 
 int /*<<< orphan*/  allocate_pool ; 
 scalar_t__ efi_call_early (int /*<<< orphan*/ ,void**,...) ; 
 scalar_t__ efi_is_64bit () ; 
 int /*<<< orphan*/  free_pool ; 
 int /*<<< orphan*/  locate_handle ; 
 scalar_t__ setup_gop32 (int /*<<< orphan*/ *,struct screen_info*,int /*<<< orphan*/ *,unsigned long,void**) ; 
 scalar_t__ setup_gop64 (int /*<<< orphan*/ *,struct screen_info*,int /*<<< orphan*/ *,unsigned long,void**) ; 

efi_status_t efi_setup_gop(efi_system_table_t *sys_table_arg,
			   struct screen_info *si, efi_guid_t *proto,
			   unsigned long size)
{
	efi_status_t status;
	void **gop_handle = NULL;

	status = efi_call_early(allocate_pool, EFI_LOADER_DATA,
				size, (void **)&gop_handle);
	if (status != EFI_SUCCESS)
		return status;

	status = efi_call_early(locate_handle,
				EFI_LOCATE_BY_PROTOCOL,
				proto, NULL, &size, gop_handle);
	if (status != EFI_SUCCESS)
		goto free_handle;

	if (efi_is_64bit()) {
		status = setup_gop64(sys_table_arg, si, proto, size,
				     gop_handle);
	} else {
		status = setup_gop32(sys_table_arg, si, proto, size,
				     gop_handle);
	}

free_handle:
	efi_call_early(free_pool, gop_handle);
	return status;
}