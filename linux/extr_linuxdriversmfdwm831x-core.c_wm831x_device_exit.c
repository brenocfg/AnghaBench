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
struct wm831x {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  WM831X_IRQ_AUXADC_DATA ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct wm831x*) ; 
 int /*<<< orphan*/  mfd_remove_devices (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wm831x_irq (struct wm831x*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wm831x_irq_exit (struct wm831x*) ; 
 int /*<<< orphan*/  wm831x_otp_exit (struct wm831x*) ; 

void wm831x_device_exit(struct wm831x *wm831x)
{
	wm831x_otp_exit(wm831x);
	mfd_remove_devices(wm831x->dev);
	free_irq(wm831x_irq(wm831x, WM831X_IRQ_AUXADC_DATA), wm831x);
	wm831x_irq_exit(wm831x);
}