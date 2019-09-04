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

/* Variables and functions */
 scalar_t__ acpi_base ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_ebook_switch () ; 
 int /*<<< orphan*/  free_ec_sci () ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct platform_device*) ; 
 int /*<<< orphan*/  free_lid_events () ; 
 int /*<<< orphan*/  free_lid_switch () ; 
 int /*<<< orphan*/  free_power_button () ; 
 int /*<<< orphan*/  mfd_cell_disable (struct platform_device*) ; 
 int /*<<< orphan*/  sci_irq ; 
 int /*<<< orphan*/  sci_work ; 

__attribute__((used)) static int xo1_sci_remove(struct platform_device *pdev)
{
	mfd_cell_disable(pdev);
	free_irq(sci_irq, pdev);
	cancel_work_sync(&sci_work);
	free_ec_sci();
	free_lid_events();
	free_lid_switch();
	free_ebook_switch();
	free_power_button();
	acpi_base = 0;
	return 0;
}