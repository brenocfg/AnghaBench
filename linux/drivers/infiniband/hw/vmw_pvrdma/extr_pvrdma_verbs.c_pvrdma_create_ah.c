#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_11__ {scalar_t__ dmac; } ;
struct rdma_ah_attr {scalar_t__ type; TYPE_5__ roce; } ;
struct pvrdma_dev {TYPE_2__* dsr; int /*<<< orphan*/  num_ahs; } ;
struct TYPE_10__ {int port_pd; int src_path_bits; int sl_tclass_flowlabel; int /*<<< orphan*/  dmac; int /*<<< orphan*/  dgid; int /*<<< orphan*/  hop_limit; int /*<<< orphan*/  gid_index; } ;
struct pvrdma_ah {TYPE_4__ av; } ;
struct in6_addr {int dummy; } ;
struct ib_udata {int dummy; } ;
struct TYPE_9__ {scalar_t__ raw; } ;
struct ib_global_route {int traffic_class; int flow_label; TYPE_3__ dgid; int /*<<< orphan*/  hop_limit; int /*<<< orphan*/  sgid_index; } ;
struct ib_ah {int /*<<< orphan*/  pd; int /*<<< orphan*/  device; } ;
struct TYPE_12__ {int pd_handle; } ;
struct TYPE_7__ {int /*<<< orphan*/  max_ah; } ;
struct TYPE_8__ {TYPE_1__ caps; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int ETH_ALEN ; 
 int IB_AH_GRH ; 
 scalar_t__ RDMA_AH_ATTR_TYPE_ROCE ; 
 int /*<<< orphan*/  atomic_add_unless (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,scalar_t__,int) ; 
 int rdma_ah_get_ah_flags (struct rdma_ah_attr*) ; 
 int rdma_ah_get_path_bits (struct rdma_ah_attr*) ; 
 int rdma_ah_get_port_num (struct rdma_ah_attr*) ; 
 struct ib_global_route* rdma_ah_read_grh (struct rdma_ah_attr*) ; 
 scalar_t__ rdma_is_multicast_addr (struct in6_addr*) ; 
 struct pvrdma_ah* to_vah (struct ib_ah*) ; 
 struct pvrdma_dev* to_vdev (int /*<<< orphan*/ ) ; 
 TYPE_6__* to_vpd (int /*<<< orphan*/ ) ; 

int pvrdma_create_ah(struct ib_ah *ibah, struct rdma_ah_attr *ah_attr,
		     u32 flags, struct ib_udata *udata)
{
	struct pvrdma_dev *dev = to_vdev(ibah->device);
	struct pvrdma_ah *ah = to_vah(ibah);
	const struct ib_global_route *grh;
	u8 port_num = rdma_ah_get_port_num(ah_attr);

	if (!(rdma_ah_get_ah_flags(ah_attr) & IB_AH_GRH))
		return -EINVAL;

	grh = rdma_ah_read_grh(ah_attr);
	if ((ah_attr->type != RDMA_AH_ATTR_TYPE_ROCE)  ||
	    rdma_is_multicast_addr((struct in6_addr *)grh->dgid.raw))
		return -EINVAL;

	if (!atomic_add_unless(&dev->num_ahs, 1, dev->dsr->caps.max_ah))
		return -ENOMEM;

	ah->av.port_pd = to_vpd(ibah->pd)->pd_handle | (port_num << 24);
	ah->av.src_path_bits = rdma_ah_get_path_bits(ah_attr);
	ah->av.src_path_bits |= 0x80;
	ah->av.gid_index = grh->sgid_index;
	ah->av.hop_limit = grh->hop_limit;
	ah->av.sl_tclass_flowlabel = (grh->traffic_class << 20) |
				      grh->flow_label;
	memcpy(ah->av.dgid, grh->dgid.raw, 16);
	memcpy(ah->av.dmac, ah_attr->roce.dmac, ETH_ALEN);

	return 0;
}