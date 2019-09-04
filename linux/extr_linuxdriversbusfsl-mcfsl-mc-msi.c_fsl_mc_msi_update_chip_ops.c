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
struct msi_domain_info {struct irq_chip* chip; } ;
struct irq_chip {scalar_t__ irq_write_msi_msg; } ;

/* Variables and functions */
 scalar_t__ fsl_mc_msi_write_msg ; 

__attribute__((used)) static void fsl_mc_msi_update_chip_ops(struct msi_domain_info *info)
{
	struct irq_chip *chip = info->chip;

	if (!chip)
		return;

	/*
	 * irq_write_msi_msg should not be set by the caller
	 */
	if (!chip->irq_write_msi_msg)
		chip->irq_write_msi_msg = fsl_mc_msi_write_msg;
}