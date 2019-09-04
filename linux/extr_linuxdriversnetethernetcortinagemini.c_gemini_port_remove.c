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
struct gemini_ethernet_port {int /*<<< orphan*/  geth; int /*<<< orphan*/  pclk; scalar_t__ netdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  geth_cleanup_freeq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unregister_netdev (scalar_t__) ; 

__attribute__((used)) static void gemini_port_remove(struct gemini_ethernet_port *port)
{
	if (port->netdev)
		unregister_netdev(port->netdev);
	clk_disable_unprepare(port->pclk);
	geth_cleanup_freeq(port->geth);
}