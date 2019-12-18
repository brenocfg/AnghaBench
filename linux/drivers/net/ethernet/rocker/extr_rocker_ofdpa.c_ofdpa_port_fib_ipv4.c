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
typedef  int /*<<< orphan*/  u32 ;
struct ofdpa_port {scalar_t__ dev; int /*<<< orphan*/  internal_vlan_id; } ;
struct fib_nh {scalar_t__ fib_nh_dev; int /*<<< orphan*/  fib_nh_gw4; } ;
struct fib_info {int /*<<< orphan*/  fib_priority; } ;
typedef  enum rocker_of_dpa_table_id { ____Placeholder_rocker_of_dpa_table_id } rocker_of_dpa_table_id ;
typedef  int /*<<< orphan*/  __be32 ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_P_IP ; 
 int /*<<< orphan*/  ROCKER_GROUP_L2_INTERFACE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ROCKER_GROUP_L3_UNICAST (int /*<<< orphan*/ ) ; 
 int ROCKER_OF_DPA_TABLE_ID_ACL_POLICY ; 
 struct fib_nh* fib_info_nh (struct fib_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inet_make_mask (int) ; 
 int /*<<< orphan*/  netdev_err (scalar_t__,char*,int,int /*<<< orphan*/ *) ; 
 int ofdpa_flow_tbl_ucast4_routing (struct ofdpa_port*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct fib_info*,int) ; 
 int ofdpa_port_ipv4_nh (struct ofdpa_port*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ofdpa_port_fib_ipv4(struct ofdpa_port *ofdpa_port,  __be32 dst,
			       int dst_len, struct fib_info *fi, u32 tb_id,
			       int flags)
{
	const struct fib_nh *nh;
	__be16 eth_type = htons(ETH_P_IP);
	__be32 dst_mask = inet_make_mask(dst_len);
	__be16 internal_vlan_id = ofdpa_port->internal_vlan_id;
	u32 priority = fi->fib_priority;
	enum rocker_of_dpa_table_id goto_tbl =
		ROCKER_OF_DPA_TABLE_ID_ACL_POLICY;
	u32 group_id;
	bool nh_on_port;
	bool has_gw;
	u32 index;
	int err;

	/* XXX support ECMP */

	nh = fib_info_nh(fi, 0);
	nh_on_port = (nh->fib_nh_dev == ofdpa_port->dev);
	has_gw = !!nh->fib_nh_gw4;

	if (has_gw && nh_on_port) {
		err = ofdpa_port_ipv4_nh(ofdpa_port, flags,
					 nh->fib_nh_gw4, &index);
		if (err)
			return err;

		group_id = ROCKER_GROUP_L3_UNICAST(index);
	} else {
		/* Send to CPU for processing */
		group_id = ROCKER_GROUP_L2_INTERFACE(internal_vlan_id, 0);
	}

	err = ofdpa_flow_tbl_ucast4_routing(ofdpa_port, eth_type, dst,
					    dst_mask, priority, goto_tbl,
					    group_id, fi, flags);
	if (err)
		netdev_err(ofdpa_port->dev, "Error (%d) IPv4 route %pI4\n",
			   err, &dst);

	return err;
}