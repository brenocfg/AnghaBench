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
 unsigned char KBC_IRQ ; 
 unsigned char MSE_IRQ ; 
 unsigned char UART1_IRQ ; 
 unsigned char UART2_IRQ ; 
 int /*<<< orphan*/  WDCF ; 
 int /*<<< orphan*/  WDTO ; 
 int /*<<< orphan*/  __sc1200wdt_read_data (int /*<<< orphan*/ ,unsigned char*) ; 
 int /*<<< orphan*/  __sc1200wdt_write_data (int /*<<< orphan*/ ,unsigned char) ; 
 int /*<<< orphan*/  sc1200wdt_lock ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 unsigned char timeout ; 

__attribute__((used)) static void sc1200wdt_start(void)
{
	unsigned char reg;
	spin_lock(&sc1200wdt_lock);

	__sc1200wdt_read_data(WDCF, &reg);
	/* assert WDO when any of the following interrupts are triggered too */
	reg |= (KBC_IRQ | MSE_IRQ | UART1_IRQ | UART2_IRQ);
	__sc1200wdt_write_data(WDCF, reg);
	/* set the timeout and get the ball rolling */
	__sc1200wdt_write_data(WDTO, timeout);

	spin_unlock(&sc1200wdt_lock);
}