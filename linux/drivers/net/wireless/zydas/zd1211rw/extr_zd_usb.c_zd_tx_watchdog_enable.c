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
struct zd_usb_tx {int watchdog_enabled; int /*<<< orphan*/  watchdog_work; } ;
struct zd_usb {struct zd_usb_tx tx; } ;

/* Variables and functions */
 int /*<<< orphan*/  ZD_TX_WATCHDOG_INTERVAL ; 
 int /*<<< orphan*/  dev_dbg_f (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  queue_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zd_usb_dev (struct zd_usb*) ; 
 int /*<<< orphan*/  zd_workqueue ; 

void zd_tx_watchdog_enable(struct zd_usb *usb)
{
	struct zd_usb_tx *tx = &usb->tx;

	if (!tx->watchdog_enabled) {
		dev_dbg_f(zd_usb_dev(usb), "\n");
		queue_delayed_work(zd_workqueue, &tx->watchdog_work,
				   ZD_TX_WATCHDOG_INTERVAL);
		tx->watchdog_enabled = 1;
	}
}