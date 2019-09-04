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
 int /*<<< orphan*/  udbg_flush ; 
 int /*<<< orphan*/  udbg_getc ; 
 int /*<<< orphan*/  udbg_getc_poll ; 
 int /*<<< orphan*/  udbg_putc ; 
 int /*<<< orphan*/  udbg_uart_flush ; 
 int /*<<< orphan*/  udbg_uart_getc ; 
 int /*<<< orphan*/  udbg_uart_getc_poll ; 
 int /*<<< orphan*/  udbg_uart_putc ; 

__attribute__((used)) static void udbg_use_uart(void)
{
	udbg_putc = udbg_uart_putc;
	udbg_flush = udbg_uart_flush;
	udbg_getc = udbg_uart_getc;
	udbg_getc_poll = udbg_uart_getc_poll;
}