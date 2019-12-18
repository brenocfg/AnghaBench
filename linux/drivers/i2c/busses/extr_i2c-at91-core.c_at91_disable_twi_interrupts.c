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
struct at91_twi_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AT91_TWI_IDR ; 
 int /*<<< orphan*/  AT91_TWI_INT_MASK ; 
 int /*<<< orphan*/  at91_twi_write (struct at91_twi_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void at91_disable_twi_interrupts(struct at91_twi_dev *dev)
{
	at91_twi_write(dev, AT91_TWI_IDR, AT91_TWI_INT_MASK);
}