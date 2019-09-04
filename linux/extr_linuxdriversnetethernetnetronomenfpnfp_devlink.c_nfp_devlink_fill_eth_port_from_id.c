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
struct nfp_port {int dummy; } ;
struct nfp_pf {int dummy; } ;
struct nfp_eth_table_port {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFP_PORT_PHYS_PORT ; 
 int nfp_devlink_fill_eth_port (struct nfp_port*,struct nfp_eth_table_port*) ; 
 struct nfp_port* nfp_port_from_id (struct nfp_pf*,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int
nfp_devlink_fill_eth_port_from_id(struct nfp_pf *pf, unsigned int port_index,
				  struct nfp_eth_table_port *copy)
{
	struct nfp_port *port;

	port = nfp_port_from_id(pf, NFP_PORT_PHYS_PORT, port_index);

	return nfp_devlink_fill_eth_port(port, copy);
}