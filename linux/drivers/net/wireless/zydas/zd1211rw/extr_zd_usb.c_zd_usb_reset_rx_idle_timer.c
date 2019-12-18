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
struct zd_usb_rx {int /*<<< orphan*/  idle_work; } ;
struct zd_usb {struct zd_usb_rx rx; } ;

/* Variables and functions */
 int /*<<< orphan*/  ZD_RX_IDLE_INTERVAL ; 
 int /*<<< orphan*/  mod_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zd_workqueue ; 

void zd_usb_reset_rx_idle_timer(struct zd_usb *usb)
{
	struct zd_usb_rx *rx = &usb->rx;

	mod_delayed_work(zd_workqueue, &rx->idle_work, ZD_RX_IDLE_INTERVAL);
}