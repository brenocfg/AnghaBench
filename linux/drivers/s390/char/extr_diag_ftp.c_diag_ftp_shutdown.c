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
 int /*<<< orphan*/  irq_subclass_unregister (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unregister_external_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void diag_ftp_shutdown(void)
{
	irq_subclass_unregister(IRQ_SUBCLASS_SERVICE_SIGNAL);
	unregister_external_irq(EXT_IRQ_CP_SERVICE, diag_ftp_handler);
}