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
typedef  int u32 ;
typedef  scalar_t__ u16 ;
struct applespi_data {TYPE_1__* spi; } ;
typedef  int /*<<< orphan*/  efi_guid_t ;
typedef  int /*<<< orphan*/  efi_data ;
typedef  int /*<<< orphan*/  efi_char16_t ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  EFI_BL_LEVEL_GUID ; 
 scalar_t__ EFI_BL_LEVEL_NAME ; 
 int EFI_VARIABLE_BOOTSERVICE_ACCESS ; 
 int EFI_VARIABLE_NON_VOLATILE ; 
 int EFI_VARIABLE_RUNTIME_ACCESS ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int) ; 
 int efivar_entry_set_safe (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,unsigned long,scalar_t__*) ; 

__attribute__((used)) static void applespi_save_bl_level(struct applespi_data *applespi,
				   unsigned int level)
{
	efi_guid_t efi_guid;
	u32 efi_attr;
	unsigned long efi_data_len;
	u16 efi_data;
	int sts;

	/* Save keyboard backlight level */
	efi_guid = EFI_BL_LEVEL_GUID;
	efi_data = (u16)level;
	efi_data_len = sizeof(efi_data);
	efi_attr = EFI_VARIABLE_NON_VOLATILE | EFI_VARIABLE_BOOTSERVICE_ACCESS |
		   EFI_VARIABLE_RUNTIME_ACCESS;

	sts = efivar_entry_set_safe((efi_char16_t *)EFI_BL_LEVEL_NAME, efi_guid,
				    efi_attr, true, efi_data_len, &efi_data);
	if (sts)
		dev_warn(&applespi->spi->dev,
			 "Error saving backlight level to EFI vars: %d\n", sts);
}