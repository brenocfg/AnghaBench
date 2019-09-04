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
 scalar_t__ LSR ; 
 scalar_t__ TXR ; 
 int XMTRDY ; 
 int /*<<< orphan*/  cpu_relax () ; 
 scalar_t__ early_serial_base ; 
 int inb (scalar_t__) ; 
 int /*<<< orphan*/  outb (int,scalar_t__) ; 

__attribute__((used)) static void __attribute__((section(".inittext"))) serial_putchar(int ch)
{
	unsigned timeout = 0xffff;

	while ((inb(early_serial_base + LSR) & XMTRDY) == 0 && --timeout)
		cpu_relax();

	outb(ch, early_serial_base + TXR);
}