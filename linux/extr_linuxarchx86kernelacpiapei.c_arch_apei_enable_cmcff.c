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
struct acpi_hest_header {int dummy; } ;

/* Variables and functions */

int arch_apei_enable_cmcff(struct acpi_hest_header *hest_hdr, void *data)
{
#ifdef CONFIG_X86_MCE
	int i;
	struct acpi_hest_ia_corrected *cmc;
	struct acpi_hest_ia_error_bank *mc_bank;

	cmc = (struct acpi_hest_ia_corrected *)hest_hdr;
	if (!cmc->enabled)
		return 0;

	/*
	 * We expect HEST to provide a list of MC banks that report errors
	 * in firmware first mode. Otherwise, return non-zero value to
	 * indicate that we are done parsing HEST.
	 */
	if (!(cmc->flags & ACPI_HEST_FIRMWARE_FIRST) ||
	    !cmc->num_hardware_banks)
		return 1;

	pr_info("HEST: Enabling Firmware First mode for corrected errors.\n");

	mc_bank = (struct acpi_hest_ia_error_bank *)(cmc + 1);
	for (i = 0; i < cmc->num_hardware_banks; i++, mc_bank++)
		mce_disable_bank(mc_bank->bank_number);
#endif
	return 1;
}