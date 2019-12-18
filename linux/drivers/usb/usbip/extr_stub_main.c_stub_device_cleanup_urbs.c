#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct stub_priv {int num_urbs; int /*<<< orphan*/ * urbs; } ;
struct stub_device {TYPE_1__* udev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  stub_free_priv_and_urb (struct stub_priv*) ; 
 struct stub_priv* stub_priv_pop (struct stub_device*) ; 
 int /*<<< orphan*/  usb_kill_urb (int /*<<< orphan*/ ) ; 

void stub_device_cleanup_urbs(struct stub_device *sdev)
{
	struct stub_priv *priv;
	int i;

	dev_dbg(&sdev->udev->dev, "Stub device cleaning up urbs\n");

	while ((priv = stub_priv_pop(sdev))) {
		for (i = 0; i < priv->num_urbs; i++)
			usb_kill_urb(priv->urbs[i]);

		stub_free_priv_and_urb(priv);
	}
}