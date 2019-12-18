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
struct usbip_device {int dummy; } ;
struct stub_priv {int num_urbs; int /*<<< orphan*/ * urbs; } ;

/* Variables and functions */
 int usbip_recv_xbuff (struct usbip_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int stub_recv_xbuff(struct usbip_device *ud, struct stub_priv *priv)
{
	int ret;
	int i;

	for (i = 0; i < priv->num_urbs; i++) {
		ret = usbip_recv_xbuff(ud, priv->urbs[i]);
		if (ret < 0)
			break;
	}

	return ret;
}