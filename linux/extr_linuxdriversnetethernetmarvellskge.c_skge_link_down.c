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
struct skge_port {int /*<<< orphan*/  netdev; int /*<<< orphan*/  port; int /*<<< orphan*/  hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  LED_REG_OFF ; 
 int /*<<< orphan*/  LNK_LED_REG ; 
 int /*<<< orphan*/  SK_REG (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  link ; 
 int /*<<< orphan*/  netif_carrier_off (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_info (struct skge_port*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  netif_stop_queue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skge_write8 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void skge_link_down(struct skge_port *skge)
{
	skge_write8(skge->hw, SK_REG(skge->port, LNK_LED_REG), LED_REG_OFF);
	netif_carrier_off(skge->netdev);
	netif_stop_queue(skge->netdev);

	netif_info(skge, link, skge->netdev, "Link is down\n");
}