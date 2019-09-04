#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u16 ;
struct TYPE_7__ {struct ib_gid_attr* sgid_attr; } ;
struct TYPE_6__ {int /*<<< orphan*/  dmac; } ;
struct rdma_ah_attr {TYPE_2__ grh; TYPE_1__ roce; } ;
struct ib_udata {int dummy; } ;
struct ib_pd {int /*<<< orphan*/  device; } ;
struct TYPE_8__ {int /*<<< orphan*/  raw; } ;
struct ib_global_route {TYPE_3__ dgid; int /*<<< orphan*/  sgid_index; } ;
struct ib_gid_attr {int /*<<< orphan*/  ndev; } ;
struct ib_ah {int dummy; } ;
struct hns_roce_dev {struct device* dev; } ;
struct TYPE_9__ {int /*<<< orphan*/  sl_tclass_flowlabel; int /*<<< orphan*/  dgid; int /*<<< orphan*/  stat_rate; int /*<<< orphan*/  vlan; int /*<<< orphan*/  gid_index; int /*<<< orphan*/  port_pd; int /*<<< orphan*/  mac; } ;
struct hns_roce_ah {struct ib_ah ibah; TYPE_4__ av; } ;
struct device {int dummy; } ;
struct TYPE_10__ {int pdn; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct ib_ah* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  HNS_ROCE_GID_SIZE ; 
 int HNS_ROCE_PORT_NUM_SHIFT ; 
 int HNS_ROCE_SL_SHIFT ; 
 int HNS_ROCE_VLAN_SL_BIT_MASK ; 
 int HNS_ROCE_VLAN_SL_SHIFT ; 
 int /*<<< orphan*/  IB_RATE_10_GBPS ; 
 int /*<<< orphan*/  cpu_to_be32 (int) ; 
 int /*<<< orphan*/  cpu_to_le16 (int) ; 
 int /*<<< orphan*/  cpu_to_le32 (int) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ is_vlan_dev (int /*<<< orphan*/ ) ; 
 struct hns_roce_ah* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int rdma_ah_get_port_num (struct rdma_ah_attr*) ; 
 int rdma_ah_get_sl (struct rdma_ah_attr*) ; 
 scalar_t__ rdma_ah_get_static_rate (struct rdma_ah_attr*) ; 
 struct ib_global_route* rdma_ah_read_grh (struct rdma_ah_attr*) ; 
 struct hns_roce_dev* to_hr_dev (int /*<<< orphan*/ ) ; 
 TYPE_5__* to_hr_pd (struct ib_pd*) ; 
 int vlan_dev_vlan_id (int /*<<< orphan*/ ) ; 

struct ib_ah *hns_roce_create_ah(struct ib_pd *ibpd,
				 struct rdma_ah_attr *ah_attr,
				 struct ib_udata *udata)
{
	struct hns_roce_dev *hr_dev = to_hr_dev(ibpd->device);
	const struct ib_gid_attr *gid_attr;
	struct device *dev = hr_dev->dev;
	struct hns_roce_ah *ah;
	u16 vlan_tag = 0xffff;
	const struct ib_global_route *grh = rdma_ah_read_grh(ah_attr);

	ah = kzalloc(sizeof(*ah), GFP_ATOMIC);
	if (!ah)
		return ERR_PTR(-ENOMEM);

	/* Get mac address */
	memcpy(ah->av.mac, ah_attr->roce.dmac, ETH_ALEN);

	gid_attr = ah_attr->grh.sgid_attr;
	if (is_vlan_dev(gid_attr->ndev))
		vlan_tag = vlan_dev_vlan_id(gid_attr->ndev);

	if (vlan_tag < 0x1000)
		vlan_tag |= (rdma_ah_get_sl(ah_attr) &
			     HNS_ROCE_VLAN_SL_BIT_MASK) <<
			     HNS_ROCE_VLAN_SL_SHIFT;

	ah->av.port_pd = cpu_to_be32(to_hr_pd(ibpd)->pdn |
				     (rdma_ah_get_port_num(ah_attr) <<
				     HNS_ROCE_PORT_NUM_SHIFT));
	ah->av.gid_index = grh->sgid_index;
	ah->av.vlan = cpu_to_le16(vlan_tag);
	dev_dbg(dev, "gid_index = 0x%x,vlan = 0x%x\n", ah->av.gid_index,
		ah->av.vlan);

	if (rdma_ah_get_static_rate(ah_attr))
		ah->av.stat_rate = IB_RATE_10_GBPS;

	memcpy(ah->av.dgid, grh->dgid.raw, HNS_ROCE_GID_SIZE);
	ah->av.sl_tclass_flowlabel = cpu_to_le32(rdma_ah_get_sl(ah_attr) <<
						 HNS_ROCE_SL_SHIFT);

	return &ah->ibah;
}