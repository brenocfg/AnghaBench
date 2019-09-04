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
struct sky2_tx_le {int opcode; scalar_t__ addr; } ;
struct sky2_port {scalar_t__ tx_last_upper; scalar_t__ tx_prod; int /*<<< orphan*/  netdev; scalar_t__ tx_last_mss; scalar_t__ tx_tcpsum; scalar_t__ tx_cons; } ;

/* Variables and functions */
 int HW_OWNER ; 
 int OP_ADDR64 ; 
 struct sky2_tx_le* get_tx_le (struct sky2_port*,scalar_t__*) ; 
 int /*<<< orphan*/  netdev_reset_queue (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tx_init(struct sky2_port *sky2)
{
	struct sky2_tx_le *le;

	sky2->tx_prod = sky2->tx_cons = 0;
	sky2->tx_tcpsum = 0;
	sky2->tx_last_mss = 0;
	netdev_reset_queue(sky2->netdev);

	le = get_tx_le(sky2, &sky2->tx_prod);
	le->addr = 0;
	le->opcode = OP_ADDR64 | HW_OWNER;
	sky2->tx_last_upper = 0;
}