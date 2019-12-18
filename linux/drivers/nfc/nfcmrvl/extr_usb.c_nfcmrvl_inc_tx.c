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
struct nfcmrvl_usb_drv_data {int /*<<< orphan*/  txlock; int /*<<< orphan*/  tx_in_flight; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFCMRVL_USB_SUSPENDING ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int nfcmrvl_inc_tx(struct nfcmrvl_usb_drv_data *drv_data)
{
	unsigned long flags;
	int rv;

	spin_lock_irqsave(&drv_data->txlock, flags);
	rv = test_bit(NFCMRVL_USB_SUSPENDING, &drv_data->flags);
	if (!rv)
		drv_data->tx_in_flight++;
	spin_unlock_irqrestore(&drv_data->txlock, flags);

	return rv;
}