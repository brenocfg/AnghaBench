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
struct exit_boot_struct {int /*<<< orphan*/  new_fdt_addr; int /*<<< orphan*/  runtime_entry_count; int /*<<< orphan*/  runtime_map; } ;
struct efi_boot_memmap {int /*<<< orphan*/ * desc_size; int /*<<< orphan*/ * map_size; int /*<<< orphan*/ * map; } ;
typedef  int /*<<< orphan*/  efi_system_table_t ;
typedef  int /*<<< orphan*/  efi_status_t ;

/* Variables and functions */
 int /*<<< orphan*/  efi_get_virtmap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  update_fdt_memmap (int /*<<< orphan*/ ,struct efi_boot_memmap*) ; 

__attribute__((used)) static efi_status_t exit_boot_func(efi_system_table_t *sys_table_arg,
				   struct efi_boot_memmap *map,
				   void *priv)
{
	struct exit_boot_struct *p = priv;
	/*
	 * Update the memory map with virtual addresses. The function will also
	 * populate @runtime_map with copies of just the EFI_MEMORY_RUNTIME
	 * entries so that we can pass it straight to SetVirtualAddressMap()
	 */
	efi_get_virtmap(*map->map, *map->map_size, *map->desc_size,
			p->runtime_map, p->runtime_entry_count);

	return update_fdt_memmap(p->new_fdt_addr, map);
}