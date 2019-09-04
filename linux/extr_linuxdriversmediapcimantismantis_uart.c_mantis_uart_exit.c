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
struct mantis_pci {int /*<<< orphan*/  uart_work; } ;

/* Variables and functions */
 int /*<<< orphan*/  MANTIS_INT_IRQ1 ; 
 int /*<<< orphan*/  MANTIS_UART_CTL ; 
 int /*<<< orphan*/  flush_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mantis_mask_ints (struct mantis_pci*,int /*<<< orphan*/ ) ; 
 int mmread (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmwrite (int,int /*<<< orphan*/ ) ; 

void mantis_uart_exit(struct mantis_pci *mantis)
{
	/* disable interrupt */
	mantis_mask_ints(mantis, MANTIS_INT_IRQ1);
	mmwrite(mmread(MANTIS_UART_CTL) & 0xffef, MANTIS_UART_CTL);
	flush_work(&mantis->uart_work);
}