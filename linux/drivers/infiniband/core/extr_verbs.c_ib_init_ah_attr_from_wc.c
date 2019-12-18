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
typedef  union rdma_network_hdr {int dummy; } rdma_network_hdr ;
struct TYPE_2__ {scalar_t__ interface_id; } ;
union ib_gid {TYPE_1__ global; } ;
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
typedef  int u16 ;
struct rdma_ah_attr {int /*<<< orphan*/  type; } ;
struct ib_wc {int wc_flags; int network_hdr_type; int vlan_id; int /*<<< orphan*/  dlid_path_bits; int /*<<< orphan*/  slid; int /*<<< orphan*/  sl; } ;
struct ib_grh {int /*<<< orphan*/  version_tclass_flow; } ;
struct ib_gid_attr {int dummy; } ;
struct ib_device {int dummy; } ;
typedef  enum rdma_network_type { ____Placeholder_rdma_network_type } rdma_network_type ;
typedef  enum ib_gid_type { ____Placeholder_ib_gid_type } ib_gid_type ;

/* Variables and functions */
 int EPROTOTYPE ; 
 int IB_GID_TYPE_IB ; 
 int /*<<< orphan*/  IB_SA_WELL_KNOWN_GUID ; 
 int IB_WC_GRH ; 
 int IB_WC_WITH_NETWORK_HDR_TYPE ; 
 int IB_WC_WITH_VLAN ; 
 scalar_t__ IS_ERR (struct ib_gid_attr const*) ; 
 int PTR_ERR (struct ib_gid_attr const*) ; 
 int RDMA_NETWORK_IB ; 
 int be32_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ cpu_to_be64 (int /*<<< orphan*/ ) ; 
 struct ib_gid_attr* get_sgid_attr_from_eth (struct ib_device*,int /*<<< orphan*/ ,int,union ib_gid*,int) ; 
 int ib_get_gids_from_rdma_hdr (union rdma_network_hdr*,int,union ib_gid*,union ib_gid*) ; 
 int ib_get_net_type_by_grh (struct ib_device*,int /*<<< orphan*/ ,struct ib_grh const*) ; 
 int ib_network_to_gid_type (int) ; 
 int ib_resolve_unicast_gid_dmac (struct ib_device*,struct rdma_ah_attr*) ; 
 int /*<<< orphan*/  memset (struct rdma_ah_attr*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  might_sleep () ; 
 int /*<<< orphan*/  rdma_ah_find_type (struct ib_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rdma_ah_set_dlid (struct rdma_ah_attr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rdma_ah_set_path_bits (struct rdma_ah_attr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rdma_ah_set_port_num (struct rdma_ah_attr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rdma_ah_set_sl (struct rdma_ah_attr*,int /*<<< orphan*/ ) ; 
 scalar_t__ rdma_cap_eth_ah (struct ib_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rdma_destroy_ah_attr (struct rdma_ah_attr*) ; 
 struct ib_gid_attr* rdma_find_gid_by_port (struct ib_device*,union ib_gid*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct ib_gid_attr* rdma_get_gid_attr (struct ib_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rdma_move_grh_sgid_attr (struct rdma_ah_attr*,union ib_gid*,int,int,int,struct ib_gid_attr const*) ; 
 scalar_t__ rdma_protocol_roce (struct ib_device*,int /*<<< orphan*/ ) ; 

int ib_init_ah_attr_from_wc(struct ib_device *device, u8 port_num,
			    const struct ib_wc *wc, const struct ib_grh *grh,
			    struct rdma_ah_attr *ah_attr)
{
	u32 flow_class;
	int ret;
	enum rdma_network_type net_type = RDMA_NETWORK_IB;
	enum ib_gid_type gid_type = IB_GID_TYPE_IB;
	const struct ib_gid_attr *sgid_attr;
	int hoplimit = 0xff;
	union ib_gid dgid;
	union ib_gid sgid;

	might_sleep();

	memset(ah_attr, 0, sizeof *ah_attr);
	ah_attr->type = rdma_ah_find_type(device, port_num);
	if (rdma_cap_eth_ah(device, port_num)) {
		if (wc->wc_flags & IB_WC_WITH_NETWORK_HDR_TYPE)
			net_type = wc->network_hdr_type;
		else
			net_type = ib_get_net_type_by_grh(device, port_num, grh);
		gid_type = ib_network_to_gid_type(net_type);
	}
	ret = ib_get_gids_from_rdma_hdr((union rdma_network_hdr *)grh, net_type,
					&sgid, &dgid);
	if (ret)
		return ret;

	rdma_ah_set_sl(ah_attr, wc->sl);
	rdma_ah_set_port_num(ah_attr, port_num);

	if (rdma_protocol_roce(device, port_num)) {
		u16 vlan_id = wc->wc_flags & IB_WC_WITH_VLAN ?
				wc->vlan_id : 0xffff;

		if (!(wc->wc_flags & IB_WC_GRH))
			return -EPROTOTYPE;

		sgid_attr = get_sgid_attr_from_eth(device, port_num,
						   vlan_id, &dgid,
						   gid_type);
		if (IS_ERR(sgid_attr))
			return PTR_ERR(sgid_attr);

		flow_class = be32_to_cpu(grh->version_tclass_flow);
		rdma_move_grh_sgid_attr(ah_attr,
					&sgid,
					flow_class & 0xFFFFF,
					hoplimit,
					(flow_class >> 20) & 0xFF,
					sgid_attr);

		ret = ib_resolve_unicast_gid_dmac(device, ah_attr);
		if (ret)
			rdma_destroy_ah_attr(ah_attr);

		return ret;
	} else {
		rdma_ah_set_dlid(ah_attr, wc->slid);
		rdma_ah_set_path_bits(ah_attr, wc->dlid_path_bits);

		if ((wc->wc_flags & IB_WC_GRH) == 0)
			return 0;

		if (dgid.global.interface_id !=
					cpu_to_be64(IB_SA_WELL_KNOWN_GUID)) {
			sgid_attr = rdma_find_gid_by_port(
				device, &dgid, IB_GID_TYPE_IB, port_num, NULL);
		} else
			sgid_attr = rdma_get_gid_attr(device, port_num, 0);

		if (IS_ERR(sgid_attr))
			return PTR_ERR(sgid_attr);
		flow_class = be32_to_cpu(grh->version_tclass_flow);
		rdma_move_grh_sgid_attr(ah_attr,
					&sgid,
					flow_class & 0xFFFFF,
					hoplimit,
					(flow_class >> 20) & 0xFF,
					sgid_attr);

		return 0;
	}
}