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
struct notifier_block {int dummy; } ;
struct net_device {char* name; } ;
struct can_priv {int /*<<< orphan*/  rxtx_led_trig; int /*<<< orphan*/  rx_led_trig; int /*<<< orphan*/  tx_led_trig; } ;
typedef  int /*<<< orphan*/  name ;

/* Variables and functions */
 int CAN_LED_NAME_SZ ; 
 unsigned long NETDEV_CHANGENAME ; 
 int NOTIFY_DONE ; 
 int /*<<< orphan*/  led_trigger_rename_static (char*,int /*<<< orphan*/ ) ; 
 struct net_device* netdev_notifier_info_to_dev (void*) ; 
 struct can_priv* safe_candev_priv (struct net_device*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*) ; 

__attribute__((used)) static int can_led_notifier(struct notifier_block *nb, unsigned long msg,
			    void *ptr)
{
	struct net_device *netdev = netdev_notifier_info_to_dev(ptr);
	struct can_priv *priv = safe_candev_priv(netdev);
	char name[CAN_LED_NAME_SZ];

	if (!priv)
		return NOTIFY_DONE;

	if (!priv->tx_led_trig || !priv->rx_led_trig || !priv->rxtx_led_trig)
		return NOTIFY_DONE;

	if (msg == NETDEV_CHANGENAME) {
		snprintf(name, sizeof(name), "%s-tx", netdev->name);
		led_trigger_rename_static(name, priv->tx_led_trig);

		snprintf(name, sizeof(name), "%s-rx", netdev->name);
		led_trigger_rename_static(name, priv->rx_led_trig);

		snprintf(name, sizeof(name), "%s-rxtx", netdev->name);
		led_trigger_rename_static(name, priv->rxtx_led_trig);
	}

	return NOTIFY_DONE;
}