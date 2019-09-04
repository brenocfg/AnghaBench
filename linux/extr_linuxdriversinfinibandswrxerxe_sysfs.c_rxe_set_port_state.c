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
struct rxe_dev {int dummy; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 struct rxe_dev* net_to_rxe (struct net_device*) ; 
 scalar_t__ netif_carrier_ok (struct net_device*) ; 
 scalar_t__ netif_running (struct net_device*) ; 
 int /*<<< orphan*/  rxe_port_down (struct rxe_dev*) ; 
 int /*<<< orphan*/  rxe_port_up (struct rxe_dev*) ; 

__attribute__((used)) static void rxe_set_port_state(struct net_device *ndev)
{
	struct rxe_dev *rxe = net_to_rxe(ndev);
	bool is_up = netif_running(ndev) && netif_carrier_ok(ndev);

	if (!rxe)
		goto out;

	if (is_up)
		rxe_port_up(rxe);
	else
		rxe_port_down(rxe); /* down for unknown state */
out:
	return;
}