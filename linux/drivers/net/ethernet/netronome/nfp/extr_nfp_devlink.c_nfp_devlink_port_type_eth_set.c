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
struct nfp_port {int /*<<< orphan*/  netdev; int /*<<< orphan*/  dl_port; } ;

/* Variables and functions */
 int /*<<< orphan*/  devlink_port_type_eth_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void nfp_devlink_port_type_eth_set(struct nfp_port *port)
{
	devlink_port_type_eth_set(&port->dl_port, port->netdev);
}