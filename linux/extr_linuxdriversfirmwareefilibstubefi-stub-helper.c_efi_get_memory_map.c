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
typedef  int /*<<< orphan*/  u32 ;
struct efi_boot_memmap {int* desc_size; int* map_size; int* buff_size; unsigned long* key_ptr; int /*<<< orphan*/ ** map; int /*<<< orphan*/ * desc_ver; } ;
typedef  int /*<<< orphan*/  efi_system_table_t ;
typedef  scalar_t__ efi_status_t ;
typedef  int /*<<< orphan*/  efi_memory_desc_t ;

/* Variables and functions */
 scalar_t__ EFI_BUFFER_TOO_SMALL ; 
 int /*<<< orphan*/  EFI_LOADER_DATA ; 
 int EFI_MMAP_NR_SLACK_SLOTS ; 
 scalar_t__ EFI_SUCCESS ; 
 int /*<<< orphan*/  allocate_pool ; 
 scalar_t__ efi_call_early (int /*<<< orphan*/ ,int*,...) ; 
 int /*<<< orphan*/  free_pool ; 
 int /*<<< orphan*/  get_memory_map ; 
 int /*<<< orphan*/  mmap_has_headroom (int,int,int) ; 

efi_status_t efi_get_memory_map(efi_system_table_t *sys_table_arg,
				struct efi_boot_memmap *map)
{
	efi_memory_desc_t *m = NULL;
	efi_status_t status;
	unsigned long key;
	u32 desc_version;

	*map->desc_size =	sizeof(*m);
	*map->map_size =	*map->desc_size * 32;
	*map->buff_size =	*map->map_size;
again:
	status = efi_call_early(allocate_pool, EFI_LOADER_DATA,
				*map->map_size, (void **)&m);
	if (status != EFI_SUCCESS)
		goto fail;

	*map->desc_size = 0;
	key = 0;
	status = efi_call_early(get_memory_map, map->map_size, m,
				&key, map->desc_size, &desc_version);
	if (status == EFI_BUFFER_TOO_SMALL ||
	    !mmap_has_headroom(*map->buff_size, *map->map_size,
			       *map->desc_size)) {
		efi_call_early(free_pool, m);
		/*
		 * Make sure there is some entries of headroom so that the
		 * buffer can be reused for a new map after allocations are
		 * no longer permitted.  Its unlikely that the map will grow to
		 * exceed this headroom once we are ready to trigger
		 * ExitBootServices()
		 */
		*map->map_size += *map->desc_size * EFI_MMAP_NR_SLACK_SLOTS;
		*map->buff_size = *map->map_size;
		goto again;
	}

	if (status != EFI_SUCCESS)
		efi_call_early(free_pool, m);

	if (map->key_ptr && status == EFI_SUCCESS)
		*map->key_ptr = key;
	if (map->desc_ver && status == EFI_SUCCESS)
		*map->desc_ver = desc_version;

fail:
	*map->map = m;
	return status;
}