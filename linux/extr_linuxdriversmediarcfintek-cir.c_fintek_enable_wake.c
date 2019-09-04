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
struct fintek_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_PME_CIR_BIT ; 
 int /*<<< orphan*/  ACPI_STATE_CIR_BIT ; 
 int /*<<< orphan*/  ACPI_WAKE_EN_CIR_BIT ; 
 int /*<<< orphan*/  LDEV_ACPI_PME_CLR_REG ; 
 int /*<<< orphan*/  LDEV_ACPI_PME_EN_REG ; 
 int /*<<< orphan*/  LDEV_ACPI_STATE_REG ; 
 int /*<<< orphan*/  LDEV_ACPI_WAKE_EN_REG ; 
 int /*<<< orphan*/  LOGICAL_DEV_ACPI ; 
 int /*<<< orphan*/  fintek_config_mode_disable (struct fintek_dev*) ; 
 int /*<<< orphan*/  fintek_config_mode_enable (struct fintek_dev*) ; 
 int /*<<< orphan*/  fintek_select_logical_dev (struct fintek_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fintek_set_reg_bit (struct fintek_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void fintek_enable_wake(struct fintek_dev *fintek)
{
	fintek_config_mode_enable(fintek);
	fintek_select_logical_dev(fintek, LOGICAL_DEV_ACPI);

	/* Allow CIR PME's to wake system */
	fintek_set_reg_bit(fintek, ACPI_WAKE_EN_CIR_BIT, LDEV_ACPI_WAKE_EN_REG);
	/* Enable CIR PME's */
	fintek_set_reg_bit(fintek, ACPI_PME_CIR_BIT, LDEV_ACPI_PME_EN_REG);
	/* Clear CIR PME status register */
	fintek_set_reg_bit(fintek, ACPI_PME_CIR_BIT, LDEV_ACPI_PME_CLR_REG);
	/* Save state */
	fintek_set_reg_bit(fintek, ACPI_STATE_CIR_BIT, LDEV_ACPI_STATE_REG);

	fintek_config_mode_disable(fintek);
}