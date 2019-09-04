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
struct skge_port {scalar_t__ duplex; int /*<<< orphan*/  flow_status; int /*<<< orphan*/  speed; int /*<<< orphan*/  netdev; int /*<<< orphan*/  port; int /*<<< orphan*/  hw; } ;

/* Variables and functions */
 scalar_t__ DUPLEX_FULL ; 
 int LED_BLK_OFF ; 
 int LED_REG_ON ; 
 int LED_SYNC_OFF ; 
 int /*<<< orphan*/  LNK_LED_REG ; 
 int /*<<< orphan*/  SK_REG (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  link ; 
 int /*<<< orphan*/  netif_carrier_on (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_info (struct skge_port*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_wake_queue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skge_pause (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skge_write8 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void skge_link_up(struct skge_port *skge)
{
	skge_write8(skge->hw, SK_REG(skge->port, LNK_LED_REG),
		    LED_BLK_OFF|LED_SYNC_OFF|LED_REG_ON);

	netif_carrier_on(skge->netdev);
	netif_wake_queue(skge->netdev);

	netif_info(skge, link, skge->netdev,
		   "Link is up at %d Mbps, %s duplex, flow control %s\n",
		   skge->speed,
		   skge->duplex == DUPLEX_FULL ? "full" : "half",
		   skge_pause(skge->flow_status));
}