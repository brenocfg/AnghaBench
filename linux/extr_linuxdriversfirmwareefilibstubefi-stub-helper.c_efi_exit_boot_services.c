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
struct efi_boot_memmap {int /*<<< orphan*/ * map; int /*<<< orphan*/ * key_ptr; int /*<<< orphan*/  desc_ver; int /*<<< orphan*/  desc_size; int /*<<< orphan*/ * map_size; int /*<<< orphan*/ * buff_size; } ;
typedef  int /*<<< orphan*/  efi_system_table_t ;
typedef  scalar_t__ efi_status_t ;
typedef  scalar_t__ (* efi_exit_boot_map_processing ) (int /*<<< orphan*/ *,struct efi_boot_memmap*,void*) ;

/* Variables and functions */
 scalar_t__ EFI_INVALID_PARAMETER ; 
 scalar_t__ EFI_SUCCESS ; 
 scalar_t__ efi_call_early (int /*<<< orphan*/ ,void*,...) ; 
 scalar_t__ efi_get_memory_map (int /*<<< orphan*/ *,struct efi_boot_memmap*) ; 
 int /*<<< orphan*/  exit_boot_services ; 
 int /*<<< orphan*/  free_pool ; 
 int /*<<< orphan*/  get_memory_map ; 

efi_status_t efi_exit_boot_services(efi_system_table_t *sys_table_arg,
				    void *handle,
				    struct efi_boot_memmap *map,
				    void *priv,
				    efi_exit_boot_map_processing priv_func)
{
	efi_status_t status;

	status = efi_get_memory_map(sys_table_arg, map);

	if (status != EFI_SUCCESS)
		goto fail;

	status = priv_func(sys_table_arg, map, priv);
	if (status != EFI_SUCCESS)
		goto free_map;

	status = efi_call_early(exit_boot_services, handle, *map->key_ptr);

	if (status == EFI_INVALID_PARAMETER) {
		/*
		 * The memory map changed between efi_get_memory_map() and
		 * exit_boot_services().  Per the UEFI Spec v2.6, Section 6.4:
		 * EFI_BOOT_SERVICES.ExitBootServices we need to get the
		 * updated map, and try again.  The spec implies one retry
		 * should be sufficent, which is confirmed against the EDK2
		 * implementation.  Per the spec, we can only invoke
		 * get_memory_map() and exit_boot_services() - we cannot alloc
		 * so efi_get_memory_map() cannot be used, and we must reuse
		 * the buffer.  For all practical purposes, the headroom in the
		 * buffer should account for any changes in the map so the call
		 * to get_memory_map() is expected to succeed here.
		 */
		*map->map_size = *map->buff_size;
		status = efi_call_early(get_memory_map,
					map->map_size,
					*map->map,
					map->key_ptr,
					map->desc_size,
					map->desc_ver);

		/* exit_boot_services() was called, thus cannot free */
		if (status != EFI_SUCCESS)
			goto fail;

		status = priv_func(sys_table_arg, map, priv);
		/* exit_boot_services() was called, thus cannot free */
		if (status != EFI_SUCCESS)
			goto fail;

		status = efi_call_early(exit_boot_services, handle, *map->key_ptr);
	}

	/* exit_boot_services() was called, thus cannot free */
	if (status != EFI_SUCCESS)
		goto fail;

	return EFI_SUCCESS;

free_map:
	efi_call_early(free_pool, *map->map);
fail:
	return status;
}