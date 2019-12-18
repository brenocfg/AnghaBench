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
struct p54u_priv {int /*<<< orphan*/  fw; int /*<<< orphan*/  fw_wait_load; } ;
struct ieee80211_hw {struct p54u_priv* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  p54_free_common (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  p54_unregister_common (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  release_firmware (int /*<<< orphan*/ ) ; 
 struct ieee80211_hw* usb_get_intfdata (struct usb_interface*) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void p54u_disconnect(struct usb_interface *intf)
{
	struct ieee80211_hw *dev = usb_get_intfdata(intf);
	struct p54u_priv *priv;

	if (!dev)
		return;

	priv = dev->priv;
	wait_for_completion(&priv->fw_wait_load);
	p54_unregister_common(dev);

	release_firmware(priv->fw);
	p54_free_common(dev);
}