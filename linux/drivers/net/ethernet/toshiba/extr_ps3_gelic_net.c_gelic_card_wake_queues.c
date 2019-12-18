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
struct gelic_card {scalar_t__* netdev; } ;

/* Variables and functions */
 size_t GELIC_PORT_ETHERNET_0 ; 
 size_t GELIC_PORT_WIRELESS ; 
 int /*<<< orphan*/  netif_wake_queue (scalar_t__) ; 

__attribute__((used)) static void gelic_card_wake_queues(struct gelic_card *card)
{
	netif_wake_queue(card->netdev[GELIC_PORT_ETHERNET_0]);

	if (card->netdev[GELIC_PORT_WIRELESS])
		netif_wake_queue(card->netdev[GELIC_PORT_WIRELESS]);
}