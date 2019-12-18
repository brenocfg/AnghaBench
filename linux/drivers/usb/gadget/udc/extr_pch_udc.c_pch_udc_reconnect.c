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
struct pch_udc_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  UDC_DEVCTL_ADDR ; 
 int UDC_DEVCTL_RES ; 
 int UDC_DEVCTL_SD ; 
 int UDC_DEVINT_ENUM ; 
 int UDC_DEVINT_UR ; 
 int /*<<< orphan*/  UDC_DEVIRQMSK_ADDR ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  pch_udc_bit_clr (struct pch_udc_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pch_udc_bit_set (struct pch_udc_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pch_udc_init (struct pch_udc_dev*) ; 

__attribute__((used)) static void pch_udc_reconnect(struct pch_udc_dev *dev)
{
	pch_udc_init(dev);

	/* enable device interrupts */
	/* pch_udc_enable_interrupts() */
	pch_udc_bit_clr(dev, UDC_DEVIRQMSK_ADDR,
			UDC_DEVINT_UR | UDC_DEVINT_ENUM);

	/* Clear the disconnect */
	pch_udc_bit_set(dev, UDC_DEVCTL_ADDR, UDC_DEVCTL_RES);
	pch_udc_bit_clr(dev, UDC_DEVCTL_ADDR, UDC_DEVCTL_SD);
	mdelay(1);
	/* Resume USB signalling */
	pch_udc_bit_clr(dev, UDC_DEVCTL_ADDR, UDC_DEVCTL_RES);
}