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
struct mtk_eth {int /*<<< orphan*/ * netdev; } ;

/* Variables and functions */
 int MTK_MAC_COUNT ; 
 int /*<<< orphan*/  netif_stop_queue (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mtk_stop_queue(struct mtk_eth *eth)
{
	int i;

	for (i = 0; i < MTK_MAC_COUNT; i++) {
		if (!eth->netdev[i])
			continue;
		netif_stop_queue(eth->netdev[i]);
	}
}