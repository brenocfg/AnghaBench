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

/* Variables and functions */
 int /*<<< orphan*/  EXT_IRQ_CP_SERVICE ; 
 int /*<<< orphan*/  IRQ_SUBCLASS_SERVICE_SIGNAL ; 
 int /*<<< orphan*/  diag_ftp_handler ; 
 int /*<<< orphan*/  irq_subclass_register (int /*<<< orphan*/ ) ; 
 int register_external_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int diag_ftp_startup(void)
{
	int rc;

	rc = register_external_irq(EXT_IRQ_CP_SERVICE, diag_ftp_handler);
	if (rc)
		return rc;

	irq_subclass_register(IRQ_SUBCLASS_SERVICE_SIGNAL);
	return 0;
}