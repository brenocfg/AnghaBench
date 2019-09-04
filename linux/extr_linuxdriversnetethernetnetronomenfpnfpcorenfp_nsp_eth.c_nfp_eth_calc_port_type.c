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
struct nfp_eth_table_port {scalar_t__ interface; scalar_t__ media; int /*<<< orphan*/  port_type; } ;
struct nfp_cpp {int dummy; } ;

/* Variables and functions */
 scalar_t__ NFP_INTERFACE_NONE ; 
 scalar_t__ NFP_MEDIA_FIBRE ; 
 int /*<<< orphan*/  PORT_DA ; 
 int /*<<< orphan*/  PORT_FIBRE ; 
 int /*<<< orphan*/  PORT_NONE ; 

__attribute__((used)) static void
nfp_eth_calc_port_type(struct nfp_cpp *cpp, struct nfp_eth_table_port *entry)
{
	if (entry->interface == NFP_INTERFACE_NONE) {
		entry->port_type = PORT_NONE;
		return;
	}

	if (entry->media == NFP_MEDIA_FIBRE)
		entry->port_type = PORT_FIBRE;
	else
		entry->port_type = PORT_DA;
}