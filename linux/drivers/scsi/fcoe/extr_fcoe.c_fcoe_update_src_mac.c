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
typedef  int /*<<< orphan*/  u8 ;
struct fcoe_port {int /*<<< orphan*/ * data_src_addr; struct fcoe_interface* priv; } ;
struct fcoe_interface {int /*<<< orphan*/  netdev; } ;
struct fc_lport {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  dev_uc_add (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_uc_del (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  is_zero_ether_addr (int /*<<< orphan*/ *) ; 
 struct fcoe_port* lport_priv (struct fc_lport*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void fcoe_update_src_mac(struct fc_lport *lport, u8 *addr)
{
	struct fcoe_port *port = lport_priv(lport);
	struct fcoe_interface *fcoe = port->priv;

	if (!is_zero_ether_addr(port->data_src_addr))
		dev_uc_del(fcoe->netdev, port->data_src_addr);
	if (!is_zero_ether_addr(addr))
		dev_uc_add(fcoe->netdev, addr);
	memcpy(port->data_src_addr, addr, ETH_ALEN);
}