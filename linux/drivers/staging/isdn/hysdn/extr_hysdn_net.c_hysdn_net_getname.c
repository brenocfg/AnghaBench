#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct net_device {char* name; } ;
struct TYPE_3__ {struct net_device* netif; } ;
typedef  TYPE_1__ hysdn_card ;

/* Variables and functions */

char *
hysdn_net_getname(hysdn_card *card)
{
	struct net_device *dev = card->netif;

	if (!dev)
		return ("-");	/* non existing */

	return (dev->name);
}