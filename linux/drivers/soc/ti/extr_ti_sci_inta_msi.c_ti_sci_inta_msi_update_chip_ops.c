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
struct irq_chip {int /*<<< orphan*/  irq_ack; int /*<<< orphan*/  irq_mask; int /*<<< orphan*/  irq_unmask; int /*<<< orphan*/  irq_set_type; int /*<<< orphan*/  irq_write_msi_msg; int /*<<< orphan*/  irq_compose_msi_msg; int /*<<< orphan*/  irq_release_resources; int /*<<< orphan*/  irq_request_resources; } ;

/* Variables and functions */
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  irq_chip_ack_parent ; 
 int /*<<< orphan*/  irq_chip_mask_parent ; 
 int /*<<< orphan*/  irq_chip_release_resources_parent ; 
 int /*<<< orphan*/  irq_chip_request_resources_parent ; 
 int /*<<< orphan*/  irq_chip_set_type_parent ; 
 int /*<<< orphan*/  irq_chip_unmask_parent ; 
 int /*<<< orphan*/  ti_sci_inta_msi_compose_msi_msg ; 
 int /*<<< orphan*/  ti_sci_inta_msi_write_msg ; 

__attribute__((used)) static void ti_sci_inta_msi_update_chip_ops(struct msi_domain_info *info)
{
	struct irq_chip *chip = info->chip;

	if (WARN_ON(!chip))
		return;

	chip->irq_request_resources = irq_chip_request_resources_parent;
	chip->irq_release_resources = irq_chip_release_resources_parent;
	chip->irq_compose_msi_msg = ti_sci_inta_msi_compose_msi_msg;
	chip->irq_write_msi_msg = ti_sci_inta_msi_write_msg;
	chip->irq_set_type = irq_chip_set_type_parent;
	chip->irq_unmask = irq_chip_unmask_parent;
	chip->irq_mask = irq_chip_mask_parent;
	chip->irq_ack = irq_chip_ack_parent;
}