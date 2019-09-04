#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ esrt; } ;

/* Variables and functions */
 int /*<<< orphan*/  EFI_CONFIG_TABLES ; 
 scalar_t__ EFI_INVALID_TABLE_ADDR ; 
 TYPE_1__ efi ; 
 int /*<<< orphan*/  efi_enabled (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int esrt_table_exists(void)
{
	if (!efi_enabled(EFI_CONFIG_TABLES))
		return 0;
	if (efi.esrt == EFI_INVALID_TABLE_ADDR)
		return 0;
	return 1;
}