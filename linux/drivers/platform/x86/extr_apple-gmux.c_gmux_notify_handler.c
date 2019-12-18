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
typedef  int u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct pnp_dev {int dummy; } ;
struct apple_gmux_data {int /*<<< orphan*/  powerchange_done; } ;
typedef  int /*<<< orphan*/  acpi_handle ;

/* Variables and functions */
 int GMUX_INTERRUPT_STATUS_POWER ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gmux_clear_interrupts (struct apple_gmux_data*) ; 
 int /*<<< orphan*/  gmux_disable_interrupts (struct apple_gmux_data*) ; 
 int /*<<< orphan*/  gmux_enable_interrupts (struct apple_gmux_data*) ; 
 int gmux_interrupt_get_status (struct apple_gmux_data*) ; 
 struct apple_gmux_data* pnp_get_drvdata (struct pnp_dev*) ; 
 int /*<<< orphan*/  pr_debug (char*,int) ; 

__attribute__((used)) static void gmux_notify_handler(acpi_handle device, u32 value, void *context)
{
	u8 status;
	struct pnp_dev *pnp = (struct pnp_dev *)context;
	struct apple_gmux_data *gmux_data = pnp_get_drvdata(pnp);

	status = gmux_interrupt_get_status(gmux_data);
	gmux_disable_interrupts(gmux_data);
	pr_debug("Notify handler called: status %d\n", status);

	gmux_clear_interrupts(gmux_data);
	gmux_enable_interrupts(gmux_data);

	if (status & GMUX_INTERRUPT_STATUS_POWER)
		complete(&gmux_data->powerchange_done);
}