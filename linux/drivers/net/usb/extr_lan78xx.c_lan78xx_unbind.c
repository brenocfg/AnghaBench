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
struct usb_interface {int dummy; } ;
struct lan78xx_priv {int /*<<< orphan*/  set_vlan; int /*<<< orphan*/  set_multicast; } ;
struct lan78xx_net {scalar_t__* data; int /*<<< orphan*/  net; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ifdown ; 
 int /*<<< orphan*/  kfree (struct lan78xx_priv*) ; 
 int /*<<< orphan*/  lan78xx_remove_irq_domain (struct lan78xx_net*) ; 
 int /*<<< orphan*/  lan78xx_remove_mdio (struct lan78xx_net*) ; 
 int /*<<< orphan*/  netif_dbg (struct lan78xx_net*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void lan78xx_unbind(struct lan78xx_net *dev, struct usb_interface *intf)
{
	struct lan78xx_priv *pdata = (struct lan78xx_priv *)(dev->data[0]);

	lan78xx_remove_irq_domain(dev);

	lan78xx_remove_mdio(dev);

	if (pdata) {
		cancel_work_sync(&pdata->set_multicast);
		cancel_work_sync(&pdata->set_vlan);
		netif_dbg(dev, ifdown, dev->net, "free pdata");
		kfree(pdata);
		pdata = NULL;
		dev->data[0] = 0;
	}
}