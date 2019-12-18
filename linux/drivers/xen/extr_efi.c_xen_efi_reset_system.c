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
typedef  int /*<<< orphan*/  efi_status_t ;
typedef  int /*<<< orphan*/  efi_char16_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
#define  EFI_RESET_COLD 130 
#define  EFI_RESET_SHUTDOWN 129 
#define  EFI_RESET_WARM 128 
 int /*<<< orphan*/  SHUTDOWN_poweroff ; 
 int /*<<< orphan*/  SHUTDOWN_reboot ; 
 int /*<<< orphan*/  xen_reboot (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void xen_efi_reset_system(int reset_type, efi_status_t status,
				 unsigned long data_size, efi_char16_t *data)
{
	switch (reset_type) {
	case EFI_RESET_COLD:
	case EFI_RESET_WARM:
		xen_reboot(SHUTDOWN_reboot);
		break;
	case EFI_RESET_SHUTDOWN:
		xen_reboot(SHUTDOWN_poweroff);
		break;
	default:
		BUG();
	}
}