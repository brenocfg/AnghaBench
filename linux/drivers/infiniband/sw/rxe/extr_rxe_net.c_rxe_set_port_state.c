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
struct rxe_dev {int /*<<< orphan*/  ndev; } ;

/* Variables and functions */
 scalar_t__ netif_carrier_ok (int /*<<< orphan*/ ) ; 
 scalar_t__ netif_running (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rxe_port_down (struct rxe_dev*) ; 
 int /*<<< orphan*/  rxe_port_up (struct rxe_dev*) ; 

void rxe_set_port_state(struct rxe_dev *rxe)
{
	if (netif_running(rxe->ndev) && netif_carrier_ok(rxe->ndev))
		rxe_port_up(rxe);
	else
		rxe_port_down(rxe);
}