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
typedef  int /*<<< orphan*/  u8 ;

/* Variables and functions */
 scalar_t__ MOXA_MUST_EFR_REGISTER ; 
 int /*<<< orphan*/  MOXA_MUST_EFR_SF_MASK ; 
 int /*<<< orphan*/  MOXA_MUST_ENTER_ENCHANCE ; 
 scalar_t__ UART_LCR ; 
 int /*<<< orphan*/  inb (scalar_t__) ; 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void SET_MOXA_MUST_NO_SOFTWARE_FLOW_CONTROL(unsigned long baseio)
{
	u8 oldlcr;
	u8 efr;

	oldlcr = inb(baseio + UART_LCR);
	outb(MOXA_MUST_ENTER_ENCHANCE, baseio + UART_LCR);

	efr = inb(baseio + MOXA_MUST_EFR_REGISTER);
	efr &= ~MOXA_MUST_EFR_SF_MASK;

	outb(efr, baseio + MOXA_MUST_EFR_REGISTER);
	outb(oldlcr, baseio + UART_LCR);
}