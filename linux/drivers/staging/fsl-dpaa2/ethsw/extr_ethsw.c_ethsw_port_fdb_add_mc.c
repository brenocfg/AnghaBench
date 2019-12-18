#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ethsw_port_priv {int /*<<< orphan*/  netdev; TYPE_1__* ethsw_data; int /*<<< orphan*/  idx; } ;
struct dpsw_fdb_multicast_cfg {int num_ifs; int /*<<< orphan*/ * if_id; int /*<<< orphan*/  type; int /*<<< orphan*/  mac_addr; int /*<<< orphan*/  member_0; } ;
struct TYPE_2__ {int /*<<< orphan*/  dpsw_handle; int /*<<< orphan*/  mc_io; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPSW_FDB_ENTRY_STATIC ; 
 int ENXIO ; 
 int dpsw_fdb_add_multicast (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct dpsw_fdb_multicast_cfg*) ; 
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ ,unsigned char const*) ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int ethsw_port_fdb_add_mc(struct ethsw_port_priv *port_priv,
				 const unsigned char *addr)
{
	struct dpsw_fdb_multicast_cfg entry = {0};
	int err;

	ether_addr_copy(entry.mac_addr, addr);
	entry.type = DPSW_FDB_ENTRY_STATIC;
	entry.num_ifs = 1;
	entry.if_id[0] = port_priv->idx;

	err = dpsw_fdb_add_multicast(port_priv->ethsw_data->mc_io, 0,
				     port_priv->ethsw_data->dpsw_handle,
				     0, &entry);
	/* Silently discard error for calling multiple times the add command */
	if (err && err != -ENXIO)
		netdev_err(port_priv->netdev, "dpsw_fdb_add_multicast err %d\n",
			   err);
	return err;
}