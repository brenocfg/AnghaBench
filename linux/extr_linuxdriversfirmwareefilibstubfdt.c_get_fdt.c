#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int nr_tables; scalar_t__ tables; } ;
typedef  TYPE_1__ efi_system_table_t ;
typedef  int /*<<< orphan*/  efi_guid_t ;
struct TYPE_6__ {scalar_t__ table; int /*<<< orphan*/  guid; } ;
typedef  TYPE_2__ efi_config_table_t ;

/* Variables and functions */
 int /*<<< orphan*/  DEVICE_TREE_GUID ; 
 scalar_t__ efi_guidcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ fdt_check_header (void*) ; 
 unsigned long fdt_totalsize (void*) ; 
 int /*<<< orphan*/  pr_efi_err (TYPE_1__*,char*) ; 

void *get_fdt(efi_system_table_t *sys_table, unsigned long *fdt_size)
{
	efi_guid_t fdt_guid = DEVICE_TREE_GUID;
	efi_config_table_t *tables;
	void *fdt;
	int i;

	tables = (efi_config_table_t *) sys_table->tables;
	fdt = NULL;

	for (i = 0; i < sys_table->nr_tables; i++)
		if (efi_guidcmp(tables[i].guid, fdt_guid) == 0) {
			fdt = (void *) tables[i].table;
			if (fdt_check_header(fdt) != 0) {
				pr_efi_err(sys_table, "Invalid header detected on UEFI supplied FDT, ignoring ...\n");
				return NULL;
			}
			*fdt_size = fdt_totalsize(fdt);
			break;
	 }

	return fdt;
}