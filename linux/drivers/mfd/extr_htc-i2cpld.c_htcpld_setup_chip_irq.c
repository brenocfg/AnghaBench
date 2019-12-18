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
struct platform_device {int dummy; } ;
struct htcpld_data {struct htcpld_chip* chip; } ;
struct htcpld_chip {unsigned int irq_start; unsigned int nirqs; } ;

/* Variables and functions */
 int IRQ_NOPROBE ; 
 int IRQ_NOREQUEST ; 
 int /*<<< orphan*/  handle_simple_irq ; 
 int /*<<< orphan*/  htcpld_muxed_chip ; 
 int /*<<< orphan*/  irq_clear_status_flags (unsigned int,int) ; 
 int /*<<< orphan*/  irq_set_chip_and_handler (unsigned int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_set_chip_data (unsigned int,struct htcpld_chip*) ; 
 struct htcpld_data* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int htcpld_setup_chip_irq(
		struct platform_device *pdev,
		int chip_index)
{
	struct htcpld_data *htcpld;
	struct htcpld_chip *chip;
	unsigned int irq, irq_end;

	/* Get the platform and driver data */
	htcpld = platform_get_drvdata(pdev);
	chip = &htcpld->chip[chip_index];

	/* Setup irq handlers */
	irq_end = chip->irq_start + chip->nirqs;
	for (irq = chip->irq_start; irq < irq_end; irq++) {
		irq_set_chip_and_handler(irq, &htcpld_muxed_chip,
					 handle_simple_irq);
		irq_set_chip_data(irq, chip);
		irq_clear_status_flags(irq, IRQ_NOREQUEST | IRQ_NOPROBE);
	}

	return 0;
}