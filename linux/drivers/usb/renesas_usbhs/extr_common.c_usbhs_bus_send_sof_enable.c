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
typedef  int u16 ;
struct usbhs_priv {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DVSTCTR ; 
 int UACT ; 
 int USBRST ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  usbhs_bset (struct usbhs_priv*,int /*<<< orphan*/ ,int,int) ; 
 struct device* usbhs_priv_to_dev (struct usbhs_priv*) ; 
 int usbhs_read (struct usbhs_priv*,int /*<<< orphan*/ ) ; 

void usbhs_bus_send_sof_enable(struct usbhs_priv *priv)
{
	u16 status = usbhs_read(priv, DVSTCTR) & (USBRST | UACT);

	if (status != USBRST) {
		struct device *dev = usbhs_priv_to_dev(priv);
		dev_err(dev, "usbhs should be reset\n");
	}

	usbhs_bset(priv, DVSTCTR, (USBRST | UACT), UACT);
}