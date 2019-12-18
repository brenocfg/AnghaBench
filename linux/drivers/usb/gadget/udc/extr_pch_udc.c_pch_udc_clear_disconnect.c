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
 int /*<<< orphan*/  UDC_DEVCTL_RES ; 
 int /*<<< orphan*/  UDC_DEVCTL_SD ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  pch_udc_bit_clr (struct pch_udc_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pch_udc_bit_set (struct pch_udc_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pch_udc_clear_disconnect(struct pch_udc_dev *dev)
{
	/* Clear the disconnect */
	pch_udc_bit_set(dev, UDC_DEVCTL_ADDR, UDC_DEVCTL_RES);
	pch_udc_bit_clr(dev, UDC_DEVCTL_ADDR, UDC_DEVCTL_SD);
	mdelay(1);
	/* Resume USB signalling */
	pch_udc_bit_clr(dev, UDC_DEVCTL_ADDR, UDC_DEVCTL_RES);
}