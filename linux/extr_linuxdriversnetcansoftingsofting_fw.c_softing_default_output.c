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
struct softing_priv {int chip; struct softing* card; } ;
struct softing {TYPE_1__* pdat; } ;
struct net_device {int dummy; } ;
struct TYPE_2__ {int generation; } ;

/* Variables and functions */
 struct softing_priv* netdev_priv (struct net_device*) ; 

int softing_default_output(struct net_device *netdev)
{
	struct softing_priv *priv = netdev_priv(netdev);
	struct softing *card = priv->card;

	switch (priv->chip) {
	case 1000:
		return (card->pdat->generation < 2) ? 0xfb : 0xfa;
	case 5:
		return 0x60;
	default:
		return 0x40;
	}
}