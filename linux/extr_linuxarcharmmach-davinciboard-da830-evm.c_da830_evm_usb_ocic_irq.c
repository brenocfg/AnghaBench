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
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  da830_evm_usb11_pdata ; 
 int /*<<< orphan*/  da830_evm_usb_ocic_handler (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static irqreturn_t da830_evm_usb_ocic_irq(int irq, void *dev_id)
{
	da830_evm_usb_ocic_handler(&da830_evm_usb11_pdata, 1);
	return IRQ_HANDLED;
}