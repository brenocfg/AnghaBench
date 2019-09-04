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

/* Variables and functions */
 int /*<<< orphan*/  efi_call_early (int /*<<< orphan*/ ,struct screen_info*,...) ; 
 int /*<<< orphan*/  free_pool ; 
 int /*<<< orphan*/  install_configuration_table ; 
 int /*<<< orphan*/  screen_info_guid ; 

void free_screen_info(efi_system_table_t *sys_table_arg, struct screen_info *si)
{
	if (!si)
		return;

	efi_call_early(install_configuration_table, &screen_info_guid, NULL);
	efi_call_early(free_pool, si);
}