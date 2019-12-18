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
struct dln2_dev {int /*<<< orphan*/  usb_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dln2_free_rx_urbs (struct dln2_dev*) ; 
 int /*<<< orphan*/  kfree (struct dln2_dev*) ; 
 int /*<<< orphan*/  usb_put_dev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dln2_free(struct dln2_dev *dln2)
{
	dln2_free_rx_urbs(dln2);
	usb_put_dev(dln2->usb_dev);
	kfree(dln2);
}