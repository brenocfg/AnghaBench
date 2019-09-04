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
typedef  int u8 ;
typedef  int u32 ;
struct tpm_bios_log {scalar_t__ bios_event_log; scalar_t__ bios_event_log_end; } ;
struct tpm_chip {int flags; struct tpm_bios_log log; } ;
struct linux_efi_tpm_eventlog {int size; int version; int /*<<< orphan*/  log; } ;
struct TYPE_2__ {scalar_t__ tpm_log; } ;

/* Variables and functions */
 scalar_t__ EFI_INVALID_TABLE_ADDR ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MEMREMAP_WB ; 
 int TPM_CHIP_FLAG_TPM2 ; 
 TYPE_1__ efi ; 
 scalar_t__ kmemdup (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 struct linux_efi_tpm_eventlog* memremap (scalar_t__,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memunmap (struct linux_efi_tpm_eventlog*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 

int tpm_read_log_efi(struct tpm_chip *chip)
{

	struct linux_efi_tpm_eventlog *log_tbl;
	struct tpm_bios_log *log;
	u32 log_size;
	u8 tpm_log_version;

	if (!(chip->flags & TPM_CHIP_FLAG_TPM2))
		return -ENODEV;

	if (efi.tpm_log == EFI_INVALID_TABLE_ADDR)
		return -ENODEV;

	log = &chip->log;

	log_tbl = memremap(efi.tpm_log, sizeof(*log_tbl), MEMREMAP_WB);
	if (!log_tbl) {
		pr_err("Could not map UEFI TPM log table !\n");
		return -ENOMEM;
	}

	log_size = log_tbl->size;
	memunmap(log_tbl);

	log_tbl = memremap(efi.tpm_log, sizeof(*log_tbl) + log_size,
			   MEMREMAP_WB);
	if (!log_tbl) {
		pr_err("Could not map UEFI TPM log table payload!\n");
		return -ENOMEM;
	}

	/* malloc EventLog space */
	log->bios_event_log = kmemdup(log_tbl->log, log_size, GFP_KERNEL);
	if (!log->bios_event_log)
		goto err_memunmap;
	log->bios_event_log_end = log->bios_event_log + log_size;

	tpm_log_version = log_tbl->version;
	memunmap(log_tbl);
	return tpm_log_version;

err_memunmap:
	memunmap(log_tbl);
	return -ENOMEM;
}