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
struct nfp_port {scalar_t__ type; struct nfp_eth_table_port* eth_port; } ;
struct nfp_eth_table_port {int dummy; } ;

/* Variables and functions */
 scalar_t__ NFP_PORT_PHYS_PORT ; 

struct nfp_eth_table_port *__nfp_port_get_eth_port(struct nfp_port *port)
{
	if (!port)
		return NULL;
	if (port->type != NFP_PORT_PHYS_PORT)
		return NULL;

	return port->eth_port;
}