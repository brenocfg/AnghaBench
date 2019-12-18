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
 int /*<<< orphan*/  PULSE ; 
 unsigned long TIME_CONST ; 
 scalar_t__ UART_LSR ; 
 int UART_LSR_THRE ; 
 scalar_t__ UART_TX ; 
 int inb (scalar_t__) ; 
 scalar_t__ io ; 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void send_pulse(unsigned long len)
{
	long bytes_out = len / TIME_CONST;

	if (bytes_out == 0)
		bytes_out++;

	while (bytes_out--) {
		outb(PULSE, io + UART_TX);
		/* FIXME treba seriozne cakanie z char/serial.c */
		while (!(inb(io + UART_LSR) & UART_LSR_THRE))
			;
	}
}