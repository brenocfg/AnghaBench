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
struct usb2_clock_sel_priv {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 struct usb2_clock_sel_priv* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_put (struct device*) ; 
 int /*<<< orphan*/  usb2_clock_sel_disable_extal_only (struct usb2_clock_sel_priv*) ; 

__attribute__((used)) static int rcar_usb2_clock_sel_suspend(struct device *dev)
{
	struct usb2_clock_sel_priv *priv = dev_get_drvdata(dev);

	usb2_clock_sel_disable_extal_only(priv);
	pm_runtime_put(dev);

	return 0;
}