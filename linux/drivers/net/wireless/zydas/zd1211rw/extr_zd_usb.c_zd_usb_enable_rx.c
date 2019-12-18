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
struct zd_usb_rx {int /*<<< orphan*/  setup_mutex; } ;
struct zd_usb {struct zd_usb_rx rx; } ;

/* Variables and functions */
 int __zd_usb_enable_rx (struct zd_usb*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zd_usb_reset_rx_idle_timer (struct zd_usb*) ; 

int zd_usb_enable_rx(struct zd_usb *usb)
{
	int r;
	struct zd_usb_rx *rx = &usb->rx;

	mutex_lock(&rx->setup_mutex);
	r = __zd_usb_enable_rx(usb);
	mutex_unlock(&rx->setup_mutex);

	zd_usb_reset_rx_idle_timer(usb);

	return r;
}