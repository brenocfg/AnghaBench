#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct pcan_pccard {int chan_count; TYPE_2__* pdev; TYPE_1__* channel; } ;
struct net_device {int /*<<< orphan*/  name; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {struct net_device* netdev; } ;

/* Variables and functions */
 int IFNAMSIZ ; 
 int /*<<< orphan*/  PCC_LED (int) ; 
 int /*<<< orphan*/  PCC_LED_OFF ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  free_sja1000dev (struct net_device*) ; 
 scalar_t__ pcan_pccard_present (struct pcan_pccard*) ; 
 int /*<<< orphan*/  pcan_set_can_power (struct pcan_pccard*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pcan_set_leds (struct pcan_pccard*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlcpy (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  unregister_sja1000dev (struct net_device*) ; 

__attribute__((used)) static void pcan_free_channels(struct pcan_pccard *card)
{
	int i;
	u8 led_mask = 0;

	for (i = 0; i < card->chan_count; i++) {
		struct net_device *netdev;
		char name[IFNAMSIZ];

		led_mask |= PCC_LED(i);

		netdev = card->channel[i].netdev;
		if (!netdev)
			continue;

		strlcpy(name, netdev->name, IFNAMSIZ);

		unregister_sja1000dev(netdev);

		free_sja1000dev(netdev);

		dev_info(&card->pdev->dev, "%s removed\n", name);
	}

	/* do it only if device not removed */
	if (pcan_pccard_present(card)) {
		pcan_set_leds(card, led_mask, PCC_LED_OFF);
		pcan_set_can_power(card, 0);
	}
}