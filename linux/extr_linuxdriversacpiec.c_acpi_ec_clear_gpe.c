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
struct acpi_ec {int /*<<< orphan*/  gpe; } ;

/* Variables and functions */
 int /*<<< orphan*/  acpi_clear_gpe (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_ec_is_gpe_raised (struct acpi_ec*) ; 

__attribute__((used)) static inline void acpi_ec_clear_gpe(struct acpi_ec *ec)
{
	/*
	 * GPE STS is a W1C register, which means:
	 * 1. Software can clear it without worrying about clearing other
	 *    GPEs' STS bits when the hardware sets them in parallel.
	 * 2. As long as software can ensure only clearing it when it is
	 *    set, hardware won't set it in parallel.
	 * So software can clear GPE in any contexts.
	 * Warning: do not move the check into advance_transaction() as the
	 * EC commands will be sent without GPE raised.
	 */
	if (!acpi_ec_is_gpe_raised(ec))
		return;
	acpi_clear_gpe(NULL, ec->gpe);
}