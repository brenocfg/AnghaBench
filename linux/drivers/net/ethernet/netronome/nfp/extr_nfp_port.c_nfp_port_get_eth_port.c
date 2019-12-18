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
struct nfp_port {int /*<<< orphan*/  flags; } ;
struct nfp_eth_table_port {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFP_PORT_CHANGED ; 
 struct nfp_eth_table_port* __nfp_port_get_eth_port (struct nfp_port*) ; 
 scalar_t__ nfp_net_refresh_eth_port (struct nfp_port*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

struct nfp_eth_table_port *nfp_port_get_eth_port(struct nfp_port *port)
{
	if (!__nfp_port_get_eth_port(port))
		return NULL;

	if (test_bit(NFP_PORT_CHANGED, &port->flags))
		if (nfp_net_refresh_eth_port(port))
			return NULL;

	return __nfp_port_get_eth_port(port);
}