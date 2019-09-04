#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int attribute; int type; } ;
typedef  TYPE_1__ efi_memory_desc_t ;

/* Variables and functions */
#define  EFI_BOOT_SERVICES_CODE 132 
#define  EFI_BOOT_SERVICES_DATA 131 
#define  EFI_CONVENTIONAL_MEMORY 130 
#define  EFI_LOADER_CODE 129 
#define  EFI_LOADER_DATA 128 
 int EFI_MEMORY_WB ; 

__attribute__((used)) static int
is_memory_available (efi_memory_desc_t *md)
{
	if (!(md->attribute & EFI_MEMORY_WB))
		return 0;

	switch (md->type) {
	      case EFI_LOADER_CODE:
	      case EFI_LOADER_DATA:
	      case EFI_BOOT_SERVICES_CODE:
	      case EFI_BOOT_SERVICES_DATA:
	      case EFI_CONVENTIONAL_MEMORY:
		return 1;
	}
	return 0;
}