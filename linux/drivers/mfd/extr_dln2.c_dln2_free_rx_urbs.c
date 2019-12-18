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
struct dln2_dev {int /*<<< orphan*/ * rx_buf; int /*<<< orphan*/ * rx_urb; } ;

/* Variables and functions */
 int DLN2_MAX_URBS ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_free_urb (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dln2_free_rx_urbs(struct dln2_dev *dln2)
{
	int i;

	for (i = 0; i < DLN2_MAX_URBS; i++) {
		usb_free_urb(dln2->rx_urb[i]);
		kfree(dln2->rx_buf[i]);
	}
}