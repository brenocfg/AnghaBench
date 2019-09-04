#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  efi_system_table_t ;
typedef  scalar_t__ efi_status_t ;
typedef  int /*<<< orphan*/  efi_guid_t ;
struct TYPE_4__ {int /*<<< orphan*/  file_size; } ;
typedef  TYPE_1__ efi_file_info_t ;
typedef  void efi_file_handle_t ;
typedef  int /*<<< orphan*/  efi_char16_t ;

/* Variables and functions */
 scalar_t__ EFI_BUFFER_TOO_SMALL ; 
 int /*<<< orphan*/  EFI_FILE_INFO_ID ; 
 int /*<<< orphan*/  EFI_FILE_MODE_READ ; 
 int /*<<< orphan*/  EFI_LOADER_DATA ; 
 scalar_t__ EFI_SUCCESS ; 
 int /*<<< orphan*/  allocate_pool ; 
 scalar_t__ efi_call_early (int /*<<< orphan*/ ,TYPE_1__*,...) ; 
 scalar_t__ efi_call_proto (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,void**,unsigned long*,TYPE_1__*,...) ; 
 int /*<<< orphan*/  efi_char16_printk (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  efi_file_handle ; 
 int /*<<< orphan*/  efi_printk (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  free_pool ; 
 int /*<<< orphan*/  get_info ; 
 int /*<<< orphan*/  open ; 

__attribute__((used)) static efi_status_t efi_file_size(efi_system_table_t *sys_table_arg, void *__fh,
				  efi_char16_t *filename_16, void **handle,
				  u64 *file_sz)
{
	efi_file_handle_t *h, *fh = __fh;
	efi_file_info_t *info;
	efi_status_t status;
	efi_guid_t info_guid = EFI_FILE_INFO_ID;
	unsigned long info_sz;

	status = efi_call_proto(efi_file_handle, open, fh, &h, filename_16,
				EFI_FILE_MODE_READ, (u64)0);
	if (status != EFI_SUCCESS) {
		efi_printk(sys_table_arg, "Failed to open file: ");
		efi_char16_printk(sys_table_arg, filename_16);
		efi_printk(sys_table_arg, "\n");
		return status;
	}

	*handle = h;

	info_sz = 0;
	status = efi_call_proto(efi_file_handle, get_info, h, &info_guid,
				&info_sz, NULL);
	if (status != EFI_BUFFER_TOO_SMALL) {
		efi_printk(sys_table_arg, "Failed to get file info size\n");
		return status;
	}

grow:
	status = efi_call_early(allocate_pool, EFI_LOADER_DATA,
				info_sz, (void **)&info);
	if (status != EFI_SUCCESS) {
		efi_printk(sys_table_arg, "Failed to alloc mem for file info\n");
		return status;
	}

	status = efi_call_proto(efi_file_handle, get_info, h, &info_guid,
				&info_sz, info);
	if (status == EFI_BUFFER_TOO_SMALL) {
		efi_call_early(free_pool, info);
		goto grow;
	}

	*file_sz = info->file_size;
	efi_call_early(free_pool, info);

	if (status != EFI_SUCCESS)
		efi_printk(sys_table_arg, "Failed to get initrd info\n");

	return status;
}