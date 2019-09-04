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
struct nfp_eth_table_port {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 struct nfp_eth_table_port* __nfp_port_get_eth_port (struct nfp_port*) ; 
 int /*<<< orphan*/  memcpy (struct nfp_eth_table_port*,struct nfp_eth_table_port*,int) ; 

__attribute__((used)) static int
nfp_devlink_fill_eth_port(struct nfp_port *port,
			  struct nfp_eth_table_port *copy)
{
	struct nfp_eth_table_port *eth_port;

	eth_port = __nfp_port_get_eth_port(port);
	if (!eth_port)
		return -EINVAL;

	memcpy(copy, eth_port, sizeof(*eth_port));

	return 0;
}